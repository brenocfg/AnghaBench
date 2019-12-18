#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct rtsx_chip {int cur_clk; scalar_t__ ssc_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_CTL ; 
 int /*<<< orphan*/  CLK_DIV ; 
 int CLK_DIV_1 ; 
 int CLK_DIV_4 ; 
 int CLK_LOW_FREQ ; 
 int PHASE_NOT_RESET ; 
 int /*<<< orphan*/  SD_VPCLK0_CTL ; 
 int /*<<< orphan*/  SSC_CTL1 ; 
 int /*<<< orphan*/  SSC_CTL2 ; 
 int /*<<< orphan*/  SSC_DIV_N_0 ; 
 int SSC_RSTB ; 
 int STATUS_ERROR ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WAIT_TIME ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int switch_ssc_clock(struct rtsx_chip *chip, int clk)
{
	int retval;
	u8 n = (u8)(clk - 2), min_n, max_n;
	u8 mcu_cnt, div, max_div, ssc_depth, ssc_depth_mask;
	int sd_vpclk_phase_reset = 0;

	if (chip->cur_clk == clk)
		return STATUS_SUCCESS;

	min_n = 60;
	max_n = 120;
	max_div = CLK_DIV_4;

	dev_dbg(rtsx_dev(chip), "Switch SSC clock to %dMHz (cur_clk = %d)\n",
		clk, chip->cur_clk);

	if ((clk <= 2) || (n > max_n))
		return STATUS_FAIL;

	mcu_cnt = (u8)(125 / clk + 3);
	if (mcu_cnt > 7)
		mcu_cnt = 7;

	div = CLK_DIV_1;
	while ((n < min_n) && (div < max_div)) {
		n = (n + 2) * 2 - 2;
		div++;
	}
	dev_dbg(rtsx_dev(chip), "n = %d, div = %d\n", n, div);

	if (chip->ssc_en) {
		ssc_depth = 0x01;
		n -= 2;
	} else {
		ssc_depth = 0;
	}

	ssc_depth_mask = 0x03;

	dev_dbg(rtsx_dev(chip), "ssc_depth = %d\n", ssc_depth);

	rtsx_init_cmd(chip);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CLK_CTL, CLK_LOW_FREQ, CLK_LOW_FREQ);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CLK_DIV, 0xFF, (div << 4) | mcu_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SSC_CTL2, ssc_depth_mask, ssc_depth);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SSC_DIV_N_0, 0xFF, n);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, SSC_RSTB);
	if (sd_vpclk_phase_reset) {
		rtsx_add_cmd(chip, WRITE_REG_CMD, SD_VPCLK0_CTL,
			     PHASE_NOT_RESET, 0);
		rtsx_add_cmd(chip, WRITE_REG_CMD, SD_VPCLK0_CTL,
			     PHASE_NOT_RESET, PHASE_NOT_RESET);
	}

	retval = rtsx_send_cmd(chip, 0, WAIT_TIME);
	if (retval < 0)
		return STATUS_ERROR;

	udelay(10);
	retval = rtsx_write_register(chip, CLK_CTL, CLK_LOW_FREQ, 0);
	if (retval)
		return retval;

	chip->cur_clk = clk;

	return STATUS_SUCCESS;
}
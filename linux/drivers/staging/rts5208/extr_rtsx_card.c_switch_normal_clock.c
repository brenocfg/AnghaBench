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
struct rtsx_chip {int cur_clk; } ;

/* Variables and functions */
#define  CLK_100 137 
#define  CLK_120 136 
#define  CLK_150 135 
#define  CLK_20 134 
#define  CLK_200 133 
#define  CLK_30 132 
#define  CLK_40 131 
#define  CLK_50 130 
#define  CLK_60 129 
#define  CLK_80 128 
 int /*<<< orphan*/  CLK_CTL ; 
 int /*<<< orphan*/  CLK_DIV ; 
 int CLK_DIV_1 ; 
 int CLK_DIV_2 ; 
 int CLK_DIV_4 ; 
 int CLK_LOW_FREQ ; 
 int /*<<< orphan*/  CLK_SEL ; 
 int PHASE_NOT_RESET ; 
 int /*<<< orphan*/  SD_VPCLK0_CTL ; 
 int /*<<< orphan*/  SD_VPCLK1_CTL ; 
 int SSC_100 ; 
 int SSC_120 ; 
 int SSC_150 ; 
 int SSC_200 ; 
 int SSC_80 ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int switch_normal_clock(struct rtsx_chip *chip, int clk)
{
	int retval;
	u8 sel, div, mcu_cnt;
	int sd_vpclk_phase_reset = 0;

	if (chip->cur_clk == clk)
		return STATUS_SUCCESS;

	switch (clk) {
	case CLK_20:
		dev_dbg(rtsx_dev(chip), "Switch clock to 20MHz\n");
		sel = SSC_80;
		div = CLK_DIV_4;
		mcu_cnt = 7;
		break;

	case CLK_30:
		dev_dbg(rtsx_dev(chip), "Switch clock to 30MHz\n");
		sel = SSC_120;
		div = CLK_DIV_4;
		mcu_cnt = 7;
		break;

	case CLK_40:
		dev_dbg(rtsx_dev(chip), "Switch clock to 40MHz\n");
		sel = SSC_80;
		div = CLK_DIV_2;
		mcu_cnt = 7;
		break;

	case CLK_50:
		dev_dbg(rtsx_dev(chip), "Switch clock to 50MHz\n");
		sel = SSC_100;
		div = CLK_DIV_2;
		mcu_cnt = 6;
		break;

	case CLK_60:
		dev_dbg(rtsx_dev(chip), "Switch clock to 60MHz\n");
		sel = SSC_120;
		div = CLK_DIV_2;
		mcu_cnt = 6;
		break;

	case CLK_80:
		dev_dbg(rtsx_dev(chip), "Switch clock to 80MHz\n");
		sel = SSC_80;
		div = CLK_DIV_1;
		mcu_cnt = 5;
		break;

	case CLK_100:
		dev_dbg(rtsx_dev(chip), "Switch clock to 100MHz\n");
		sel = SSC_100;
		div = CLK_DIV_1;
		mcu_cnt = 5;
		break;

	case CLK_120:
		dev_dbg(rtsx_dev(chip), "Switch clock to 120MHz\n");
		sel = SSC_120;
		div = CLK_DIV_1;
		mcu_cnt = 5;
		break;

	case CLK_150:
		dev_dbg(rtsx_dev(chip), "Switch clock to 150MHz\n");
		sel = SSC_150;
		div = CLK_DIV_1;
		mcu_cnt = 4;
		break;

	case CLK_200:
		dev_dbg(rtsx_dev(chip), "Switch clock to 200MHz\n");
		sel = SSC_200;
		div = CLK_DIV_1;
		mcu_cnt = 4;
		break;

	default:
		dev_dbg(rtsx_dev(chip), "Try to switch to an illegal clock (%d)\n",
			clk);
		return STATUS_FAIL;
	}

	retval = rtsx_write_register(chip, CLK_CTL, 0xFF, CLK_LOW_FREQ);
	if (retval)
		return retval;
	if (sd_vpclk_phase_reset) {
		retval = rtsx_write_register(chip, SD_VPCLK0_CTL,
					     PHASE_NOT_RESET, 0);
		if (retval)
			return retval;
		retval = rtsx_write_register(chip, SD_VPCLK1_CTL,
					     PHASE_NOT_RESET, 0);
		if (retval)
			return retval;
	}
	retval = rtsx_write_register(chip, CLK_DIV, 0xFF,
				     (div << 4) | mcu_cnt);
	if (retval)
		return retval;
	retval = rtsx_write_register(chip, CLK_SEL, 0xFF, sel);
	if (retval)
		return retval;

	if (sd_vpclk_phase_reset) {
		udelay(200);
		retval = rtsx_write_register(chip, SD_VPCLK0_CTL,
					     PHASE_NOT_RESET, PHASE_NOT_RESET);
		if (retval)
			return retval;
		retval = rtsx_write_register(chip, SD_VPCLK1_CTL,
					     PHASE_NOT_RESET, PHASE_NOT_RESET);
		if (retval)
			return retval;
		udelay(200);
	}
	retval = rtsx_write_register(chip, CLK_CTL, 0xFF, 0);
	if (retval)
		return retval;

	chip->cur_clk = clk;

	return STATUS_SUCCESS;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtsx_ucr {unsigned int cur_clk; TYPE_1__* pusb_intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CLK_CHANGE ; 
 int /*<<< orphan*/  CLK_DIV ; 
 int CLK_DIV_1 ; 
 int CLK_DIV_4 ; 
 int EINVAL ; 
 int MAX_DIV_N ; 
 int MIN_DIV_N ; 
 int /*<<< orphan*/  MODE_C ; 
 int PHASE_NOT_RESET ; 
 int /*<<< orphan*/  SD_CFG1 ; 
 int SD_CLK_DIVIDE_0 ; 
 int SD_CLK_DIVIDE_128 ; 
 int SD_CLK_DIVIDE_MASK ; 
 int /*<<< orphan*/  SD_VPCLK0_CTL ; 
 int SSC_8X_EN ; 
 int /*<<< orphan*/  SSC_CTL1 ; 
 int /*<<< orphan*/  SSC_CTL2 ; 
 int SSC_DEPTH_MASK ; 
 int /*<<< orphan*/  SSC_DIV_N_0 ; 
 int SSC_RSTB ; 
 int SSC_SEL_4M ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int double_ssc_depth (int) ; 
 int revise_ssc_depth (int,int) ; 
 int /*<<< orphan*/  rtsx_usb_add_cmd (struct rtsx_ucr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_usb_init_cmd (struct rtsx_ucr*) ; 
 int rtsx_usb_send_cmd (struct rtsx_ucr*,int /*<<< orphan*/ ,int) ; 
 int rtsx_usb_write_register (struct rtsx_ucr*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int rtsx_usb_switch_clock(struct rtsx_ucr *ucr, unsigned int card_clock,
		u8 ssc_depth, bool initial_mode, bool double_clk, bool vpclk)
{
	int ret;
	u8 n, clk_divider, mcu_cnt, div;

	if (!card_clock) {
		ucr->cur_clk = 0;
		return 0;
	}

	if (initial_mode) {
		/* We use 250k(around) here, in initial stage */
		clk_divider = SD_CLK_DIVIDE_128;
		card_clock = 30000000;
	} else {
		clk_divider = SD_CLK_DIVIDE_0;
	}

	ret = rtsx_usb_write_register(ucr, SD_CFG1,
			SD_CLK_DIVIDE_MASK, clk_divider);
	if (ret < 0)
		return ret;

	card_clock /= 1000000;
	dev_dbg(&ucr->pusb_intf->dev,
			"Switch card clock to %dMHz\n", card_clock);

	if (!initial_mode && double_clk)
		card_clock *= 2;
	dev_dbg(&ucr->pusb_intf->dev,
			"Internal SSC clock: %dMHz (cur_clk = %d)\n",
			card_clock, ucr->cur_clk);

	if (card_clock == ucr->cur_clk)
		return 0;

	/* Converting clock value into internal settings: n and div */
	n = card_clock - 2;
	if ((card_clock <= 2) || (n > MAX_DIV_N))
		return -EINVAL;

	mcu_cnt = 60/card_clock + 3;
	if (mcu_cnt > 15)
		mcu_cnt = 15;

	/* Make sure that the SSC clock div_n is not less than MIN_DIV_N */

	div = CLK_DIV_1;
	while (n < MIN_DIV_N && div < CLK_DIV_4) {
		n = (n + 2) * 2 - 2;
		div++;
	}
	dev_dbg(&ucr->pusb_intf->dev, "n = %d, div = %d\n", n, div);

	if (double_clk)
		ssc_depth = double_ssc_depth(ssc_depth);

	ssc_depth = revise_ssc_depth(ssc_depth, div);
	dev_dbg(&ucr->pusb_intf->dev, "ssc_depth = %d\n", ssc_depth);

	rtsx_usb_init_cmd(ucr);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CLK_DIV, CLK_CHANGE, CLK_CHANGE);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, CLK_DIV,
			0x3F, (div << 4) | mcu_cnt);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, 0);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SSC_CTL2,
			SSC_DEPTH_MASK, ssc_depth);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SSC_DIV_N_0, 0xFF, n);
	rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SSC_CTL1, SSC_RSTB, SSC_RSTB);
	if (vpclk) {
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_VPCLK0_CTL,
				PHASE_NOT_RESET, 0);
		rtsx_usb_add_cmd(ucr, WRITE_REG_CMD, SD_VPCLK0_CTL,
				PHASE_NOT_RESET, PHASE_NOT_RESET);
	}

	ret = rtsx_usb_send_cmd(ucr, MODE_C, 2000);
	if (ret < 0)
		return ret;

	ret = rtsx_usb_write_register(ucr, SSC_CTL1, 0xff,
			SSC_RSTB | SSC_8X_EN | SSC_SEL_4M);
	if (ret < 0)
		return ret;

	/* Wait SSC clock stable */
	usleep_range(100, 1000);

	ret = rtsx_usb_write_register(ucr, CLK_DIV, CLK_CHANGE, 0);
	if (ret < 0)
		return ret;

	ucr->cur_clk = card_clock;

	return 0;
}
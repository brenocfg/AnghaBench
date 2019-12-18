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
struct ushc_data {int clock_freq; int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USHC_CLK_FREQ ; 
 int /*<<< orphan*/  USHC_CLK_FREQ_TYPE ; 
 int /*<<< orphan*/  USHC_HOST_CTRL_HIGH_SPD ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ushc_hw_set_host_ctrl (struct ushc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ushc_set_bus_freq(struct ushc_data *ushc, int clk, bool enable_hs)
{
	int ret;

	/* Hardware can't detect interrupts while the clock is off. */
	if (clk == 0)
		clk = 400000;

	ret = ushc_hw_set_host_ctrl(ushc, USHC_HOST_CTRL_HIGH_SPD,
				    enable_hs ? USHC_HOST_CTRL_HIGH_SPD : 0);
	if (ret < 0)
		return ret;

	ret = usb_control_msg(ushc->usb_dev, usb_sndctrlpipe(ushc->usb_dev, 0),
			      USHC_CLK_FREQ, USHC_CLK_FREQ_TYPE,
			      clk & 0xffff, (clk >> 16) & 0xffff, NULL, 0, 100);
	if (ret < 0)
		return ret;

	ushc->clock_freq = clk;
	return 0;
}
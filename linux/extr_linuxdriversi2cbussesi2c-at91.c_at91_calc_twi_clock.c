#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct at91_twi_pdata {int clk_offset; int clk_max_div; scalar_t__ has_hold_field; } ;
struct at91_twi_dev {int twi_cwgr_reg; TYPE_1__* dev; int /*<<< orphan*/  clk; struct at91_twi_pdata* pdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int AT91_TWI_CWGR_HOLD (int) ; 
 int AT91_TWI_CWGR_HOLD_MAX ; 
 int DIV_ROUND_UP (int,int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int,int) ; 
 int fls (int) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void at91_calc_twi_clock(struct at91_twi_dev *dev, int twi_clk)
{
	int ckdiv, cdiv, div, hold = 0;
	struct at91_twi_pdata *pdata = dev->pdata;
	int offset = pdata->clk_offset;
	int max_ckdiv = pdata->clk_max_div;
	u32 twd_hold_time_ns = 0;

	div = max(0, (int)DIV_ROUND_UP(clk_get_rate(dev->clk),
				       2 * twi_clk) - offset);
	ckdiv = fls(div >> 8);
	cdiv = div >> ckdiv;

	if (ckdiv > max_ckdiv) {
		dev_warn(dev->dev, "%d exceeds ckdiv max value which is %d.\n",
			 ckdiv, max_ckdiv);
		ckdiv = max_ckdiv;
		cdiv = 255;
	}

	if (pdata->has_hold_field) {
		of_property_read_u32(dev->dev->of_node, "i2c-sda-hold-time-ns",
				     &twd_hold_time_ns);

		/*
		 * hold time = HOLD + 3 x T_peripheral_clock
		 * Use clk rate in kHz to prevent overflows when computing
		 * hold.
		 */
		hold = DIV_ROUND_UP(twd_hold_time_ns
				    * (clk_get_rate(dev->clk) / 1000), 1000000);
		hold -= 3;
		if (hold < 0)
			hold = 0;
		if (hold > AT91_TWI_CWGR_HOLD_MAX) {
			dev_warn(dev->dev,
				 "HOLD field set to its maximum value (%d instead of %d)\n",
				 AT91_TWI_CWGR_HOLD_MAX, hold);
			hold = AT91_TWI_CWGR_HOLD_MAX;
		}
	}

	dev->twi_cwgr_reg = (ckdiv << 16) | (cdiv << 8) | cdiv
			    | AT91_TWI_CWGR_HOLD(hold);

	dev_dbg(dev->dev, "cdiv %d ckdiv %d hold %d (%d ns)\n",
		cdiv, ckdiv, hold, twd_hold_time_ns);
}
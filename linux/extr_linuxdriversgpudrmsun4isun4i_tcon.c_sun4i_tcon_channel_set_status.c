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
struct sun4i_tcon {struct clk* sclk1; int /*<<< orphan*/  regs; TYPE_1__* quirks; struct clk* dclk; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_channel_1; int /*<<< orphan*/  has_channel_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int /*<<< orphan*/  SUN4I_TCON0_CTL_REG ; 
 int /*<<< orphan*/  SUN4I_TCON0_CTL_TCON_ENABLE ; 
 int /*<<< orphan*/  SUN4I_TCON1_CTL_REG ; 
 int /*<<< orphan*/  SUN4I_TCON1_CTL_TCON_ENABLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_rate_exclusive_get (struct clk*) ; 
 int /*<<< orphan*/  clk_rate_exclusive_put (struct clk*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_tcon_channel_set_status(struct sun4i_tcon *tcon, int channel,
					  bool enabled)
{
	struct clk *clk;

	switch (channel) {
	case 0:
		WARN_ON(!tcon->quirks->has_channel_0);
		regmap_update_bits(tcon->regs, SUN4I_TCON0_CTL_REG,
				   SUN4I_TCON0_CTL_TCON_ENABLE,
				   enabled ? SUN4I_TCON0_CTL_TCON_ENABLE : 0);
		clk = tcon->dclk;
		break;
	case 1:
		WARN_ON(!tcon->quirks->has_channel_1);
		regmap_update_bits(tcon->regs, SUN4I_TCON1_CTL_REG,
				   SUN4I_TCON1_CTL_TCON_ENABLE,
				   enabled ? SUN4I_TCON1_CTL_TCON_ENABLE : 0);
		clk = tcon->sclk1;
		break;
	default:
		DRM_WARN("Unknown channel... doing nothing\n");
		return;
	}

	if (enabled) {
		clk_prepare_enable(clk);
		clk_rate_exclusive_get(clk);
	} else {
		clk_rate_exclusive_put(clk);
		clk_disable_unprepare(clk);
	}
}
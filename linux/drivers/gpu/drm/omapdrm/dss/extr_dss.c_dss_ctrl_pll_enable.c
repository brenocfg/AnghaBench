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
struct dss_pll {int id; TYPE_1__* dss; } ;
struct TYPE_2__ {int /*<<< orphan*/  syscon_pll_ctrl_offset; int /*<<< orphan*/  syscon_pll_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int) ; 
#define  DSS_PLL_HDMI 130 
#define  DSS_PLL_VIDEO1 129 
#define  DSS_PLL_VIDEO2 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

void dss_ctrl_pll_enable(struct dss_pll *pll, bool enable)
{
	unsigned int shift;
	unsigned int val;

	if (!pll->dss->syscon_pll_ctrl)
		return;

	val = !enable;

	switch (pll->id) {
	case DSS_PLL_VIDEO1:
		shift = 0;
		break;
	case DSS_PLL_VIDEO2:
		shift = 1;
		break;
	case DSS_PLL_HDMI:
		shift = 2;
		break;
	default:
		DSSERR("illegal DSS PLL ID %d\n", pll->id);
		return;
	}

	regmap_update_bits(pll->dss->syscon_pll_ctrl,
			   pll->dss->syscon_pll_ctrl_offset,
			   1 << shift, val << shift);
}
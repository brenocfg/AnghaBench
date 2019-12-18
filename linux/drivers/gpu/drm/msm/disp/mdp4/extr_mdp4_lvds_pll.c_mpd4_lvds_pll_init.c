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
struct TYPE_2__ {int /*<<< orphan*/ * init; } ;
struct mdp4_lvds_pll {TYPE_1__ pll_hw; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct clk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* devm_clk_register (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct mdp4_lvds_pll* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pll_init ; 

struct clk *mpd4_lvds_pll_init(struct drm_device *dev)
{
	struct mdp4_lvds_pll *lvds_pll;
	struct clk *clk;
	int ret;

	lvds_pll = devm_kzalloc(dev->dev, sizeof(*lvds_pll), GFP_KERNEL);
	if (!lvds_pll) {
		ret = -ENOMEM;
		goto fail;
	}

	lvds_pll->dev = dev;

	lvds_pll->pll_hw.init = &pll_init;
	clk = devm_clk_register(dev->dev, &lvds_pll->pll_hw);
	if (IS_ERR(clk)) {
		ret = PTR_ERR(clk);
		goto fail;
	}

	return clk;

fail:
	return ERR_PTR(ret);
}
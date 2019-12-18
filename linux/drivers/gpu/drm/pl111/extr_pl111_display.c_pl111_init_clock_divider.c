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
struct clk_hw {struct clk* clk; struct clk_init_data* init; } ;
struct pl111_drm_dev_private {struct clk* clk; TYPE_1__* variant; int /*<<< orphan*/  tim2_lock; struct clk_hw clk_div; } ;
struct drm_device {int /*<<< orphan*/  dev; struct pl111_drm_dev_private* dev_private; } ;
struct clk_init_data {char* name; char const** parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {scalar_t__ broken_clockdivider; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 char* __clk_get_name (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int devm_clk_hw_register (int /*<<< orphan*/ ,struct clk_hw*) ; 
 int /*<<< orphan*/  pl111_clk_div_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pl111_init_clock_divider(struct drm_device *drm)
{
	struct pl111_drm_dev_private *priv = drm->dev_private;
	struct clk *parent = devm_clk_get(drm->dev, "clcdclk");
	struct clk_hw *div = &priv->clk_div;
	const char *parent_name;
	struct clk_init_data init = {
		.name = "pl111_div",
		.ops = &pl111_clk_div_ops,
		.parent_names = &parent_name,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	};
	int ret;

	if (IS_ERR(parent)) {
		dev_err(drm->dev, "CLCD: unable to get clcdclk.\n");
		return PTR_ERR(parent);
	}

	spin_lock_init(&priv->tim2_lock);

	/* If the clock divider is broken, use the parent directly */
	if (priv->variant->broken_clockdivider) {
		priv->clk = parent;
		return 0;
	}
	parent_name = __clk_get_name(parent);
	div->init = &init;

	ret = devm_clk_hw_register(drm->dev, div);

	priv->clk = div->clk;
	return ret;
}
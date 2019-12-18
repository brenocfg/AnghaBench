#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct clk_init_data* init; } ;
struct isp_xclk {int divider; int /*<<< orphan*/  clk; TYPE_2__ hw; int /*<<< orphan*/  lock; int /*<<< orphan*/  id; struct isp_device* isp; } ;
struct isp_device {struct isp_xclk* xclks; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct clk_init_data {char* name; int num_parents; int /*<<< orphan*/ * parent_names; int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct isp_xclk*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_XCLK_A ; 
 int /*<<< orphan*/  ISP_XCLK_B ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  isp_xclk_ops ; 
 int /*<<< orphan*/  isp_xclk_parent_name ; 
 int /*<<< orphan*/  isp_xclk_src_get ; 
 int /*<<< orphan*/  of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,struct isp_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isp_xclk_init(struct isp_device *isp)
{
	struct device_node *np = isp->dev->of_node;
	struct clk_init_data init = {};
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(isp->xclks); ++i)
		isp->xclks[i].clk = ERR_PTR(-EINVAL);

	for (i = 0; i < ARRAY_SIZE(isp->xclks); ++i) {
		struct isp_xclk *xclk = &isp->xclks[i];

		xclk->isp = isp;
		xclk->id = i == 0 ? ISP_XCLK_A : ISP_XCLK_B;
		xclk->divider = 1;
		spin_lock_init(&xclk->lock);

		init.name = i == 0 ? "cam_xclka" : "cam_xclkb";
		init.ops = &isp_xclk_ops;
		init.parent_names = &isp_xclk_parent_name;
		init.num_parents = 1;

		xclk->hw.init = &init;
		/*
		 * The first argument is NULL in order to avoid circular
		 * reference, as this driver takes reference on the
		 * sensor subdevice modules and the sensors would take
		 * reference on this module through clk_get().
		 */
		xclk->clk = clk_register(NULL, &xclk->hw);
		if (IS_ERR(xclk->clk))
			return PTR_ERR(xclk->clk);
	}

	if (np)
		of_clk_add_provider(np, isp_xclk_src_get, isp);

	return 0;
}
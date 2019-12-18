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
struct isp_xclk {int /*<<< orphan*/  clk; } ;
struct isp_device {struct isp_xclk* xclks; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct isp_xclk*) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (struct device_node*) ; 

__attribute__((used)) static void isp_xclk_cleanup(struct isp_device *isp)
{
	struct device_node *np = isp->dev->of_node;
	unsigned int i;

	if (np)
		of_clk_del_provider(np);

	for (i = 0; i < ARRAY_SIZE(isp->xclks); ++i) {
		struct isp_xclk *xclk = &isp->xclks[i];

		if (!IS_ERR(xclk->clk))
			clk_unregister(xclk->clk);
	}
}
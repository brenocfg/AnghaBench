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
struct isc_device {struct isc_clk* isc_clks; TYPE_1__* dev; } ;
struct isc_clk {int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct isc_clk*) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 

void isc_clk_cleanup(struct isc_device *isc)
{
	unsigned int i;

	of_clk_del_provider(isc->dev->of_node);

	for (i = 0; i < ARRAY_SIZE(isc->isc_clks); i++) {
		struct isc_clk *isc_clk = &isc->isc_clks[i];

		if (!IS_ERR(isc_clk->clk))
			clk_unregister(isc_clk->clk);
	}
}
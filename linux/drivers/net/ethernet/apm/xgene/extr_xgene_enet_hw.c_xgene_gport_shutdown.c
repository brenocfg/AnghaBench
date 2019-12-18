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
struct xgene_enet_pdata {int /*<<< orphan*/  clk; TYPE_1__* pdev; } ;
struct device {scalar_t__ of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_gport_shutdown(struct xgene_enet_pdata *pdata)
{
	struct device *dev = &pdata->pdev->dev;

	if (dev->of_node) {
		if (!IS_ERR(pdata->clk))
			clk_disable_unprepare(pdata->clk);
	}
}
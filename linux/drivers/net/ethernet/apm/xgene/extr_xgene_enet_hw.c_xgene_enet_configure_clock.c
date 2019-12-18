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
struct xgene_enet_pdata {int phy_speed; int /*<<< orphan*/  clk; TYPE_1__* pdev; } ;
struct device {scalar_t__ of_node; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
#define  SPEED_10 129 
#define  SPEED_100 128 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct clk* clk_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int) ; 

__attribute__((used)) static void xgene_enet_configure_clock(struct xgene_enet_pdata *pdata)
{
	struct device *dev = &pdata->pdev->dev;

	if (dev->of_node) {
		struct clk *parent = clk_get_parent(pdata->clk);

		switch (pdata->phy_speed) {
		case SPEED_10:
			clk_set_rate(parent, 2500000);
			break;
		case SPEED_100:
			clk_set_rate(parent, 25000000);
			break;
		default:
			clk_set_rate(parent, 125000000);
			break;
		}
	}
#ifdef CONFIG_ACPI
	else {
		switch (pdata->phy_speed) {
		case SPEED_10:
			acpi_evaluate_object(ACPI_HANDLE(dev),
					     "S10", NULL, NULL);
			break;
		case SPEED_100:
			acpi_evaluate_object(ACPI_HANDLE(dev),
					     "S100", NULL, NULL);
			break;
		default:
			acpi_evaluate_object(ACPI_HANDLE(dev),
					     "S1G", NULL, NULL);
			break;
		}
	}
#endif
}
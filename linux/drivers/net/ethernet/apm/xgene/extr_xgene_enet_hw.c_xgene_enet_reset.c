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
struct xgene_enet_pdata {TYPE_1__* pdev; int /*<<< orphan*/  clk; scalar_t__ mdio_driver; } ;
struct device {scalar_t__ of_node; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  xgene_enet_config_ring_if_assoc (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_enet_ecc_init (struct xgene_enet_pdata*) ; 
 int /*<<< orphan*/  xgene_ring_mgr_init (struct xgene_enet_pdata*) ; 

__attribute__((used)) static int xgene_enet_reset(struct xgene_enet_pdata *pdata)
{
	struct device *dev = &pdata->pdev->dev;

	if (!xgene_ring_mgr_init(pdata))
		return -ENODEV;

	if (pdata->mdio_driver) {
		xgene_enet_config_ring_if_assoc(pdata);
		return 0;
	}

	if (dev->of_node) {
		clk_prepare_enable(pdata->clk);
		udelay(5);
		clk_disable_unprepare(pdata->clk);
		udelay(5);
		clk_prepare_enable(pdata->clk);
		udelay(5);
	} else {
#ifdef CONFIG_ACPI
		acpi_status status;

		status = acpi_evaluate_object(ACPI_HANDLE(&pdata->pdev->dev),
					      "_RST", NULL, NULL);
		if (ACPI_FAILURE(status)) {
			acpi_evaluate_object(ACPI_HANDLE(&pdata->pdev->dev),
					     "_INI", NULL, NULL);
		}
#endif
	}

	xgene_enet_ecc_init(pdata);
	xgene_enet_config_ring_if_assoc(pdata);

	return 0;
}
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
struct xgene_mdio_pdata {int /*<<< orphan*/  clk; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (TYPE_1__*) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int xgene_enet_ecc_init (struct xgene_mdio_pdata*) ; 
 int /*<<< orphan*/  xgene_gmac_reset (struct xgene_mdio_pdata*) ; 

__attribute__((used)) static int xgene_mdio_reset(struct xgene_mdio_pdata *pdata)
{
	int ret;

	if (pdata->dev->of_node) {
		clk_prepare_enable(pdata->clk);
		udelay(5);
		clk_disable_unprepare(pdata->clk);
		udelay(5);
		clk_prepare_enable(pdata->clk);
		udelay(5);
	} else {
#ifdef CONFIG_ACPI
		acpi_evaluate_object(ACPI_HANDLE(pdata->dev),
				     "_RST", NULL, NULL);
#endif
	}

	ret = xgene_enet_ecc_init(pdata);
	if (ret) {
		if (pdata->dev->of_node)
			clk_disable_unprepare(pdata->clk);
		return ret;
	}
	xgene_gmac_reset(pdata);

	return 0;
}
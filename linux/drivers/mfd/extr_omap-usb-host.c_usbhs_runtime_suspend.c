#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usbhs_omap_platform_data {int* port_mode; } ;
struct usbhs_hcd_omap {int nports; int /*<<< orphan*/  ehci_logic_fck; int /*<<< orphan*/ * utmi_clk; int /*<<< orphan*/ * hsic480m_clk; int /*<<< orphan*/ * hsic60m_clk; struct usbhs_omap_platform_data* pdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  OMAP_EHCI_PORT_MODE_HSIC 129 
#define  OMAP_EHCI_PORT_MODE_TLL 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct usbhs_hcd_omap* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  omap_tll_disable (struct usbhs_omap_platform_data*) ; 

__attribute__((used)) static int usbhs_runtime_suspend(struct device *dev)
{
	struct usbhs_hcd_omap		*omap = dev_get_drvdata(dev);
	struct usbhs_omap_platform_data	*pdata = omap->pdata;
	int i;

	dev_dbg(dev, "usbhs_runtime_suspend\n");

	for (i = 0; i < omap->nports; i++) {
		switch (pdata->port_mode[i]) {
		case OMAP_EHCI_PORT_MODE_HSIC:
			if (!IS_ERR(omap->hsic60m_clk[i]))
				clk_disable_unprepare(omap->hsic60m_clk[i]);

			if (!IS_ERR(omap->hsic480m_clk[i]))
				clk_disable_unprepare(omap->hsic480m_clk[i]);
		/* Fall through - as utmi_clks were used in HSIC mode */

		case OMAP_EHCI_PORT_MODE_TLL:
			if (!IS_ERR(omap->utmi_clk[i]))
				clk_disable_unprepare(omap->utmi_clk[i]);
			break;
		default:
			break;
		}
	}

	if (!IS_ERR(omap->ehci_logic_fck))
		clk_disable_unprepare(omap->ehci_logic_fck);

	omap_tll_disable(pdata);

	return 0;
}
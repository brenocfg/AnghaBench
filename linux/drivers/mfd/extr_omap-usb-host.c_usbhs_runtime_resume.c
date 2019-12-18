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
struct usbhs_hcd_omap {int nports; int /*<<< orphan*/ * utmi_clk; int /*<<< orphan*/ * hsic480m_clk; int /*<<< orphan*/ * hsic60m_clk; int /*<<< orphan*/  ehci_logic_fck; struct usbhs_omap_platform_data* pdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  OMAP_EHCI_PORT_MODE_HSIC 129 
#define  OMAP_EHCI_PORT_MODE_TLL 128 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 struct usbhs_hcd_omap* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  omap_tll_enable (struct usbhs_omap_platform_data*) ; 

__attribute__((used)) static int usbhs_runtime_resume(struct device *dev)
{
	struct usbhs_hcd_omap		*omap = dev_get_drvdata(dev);
	struct usbhs_omap_platform_data	*pdata = omap->pdata;
	int i, r;

	dev_dbg(dev, "usbhs_runtime_resume\n");

	omap_tll_enable(pdata);

	if (!IS_ERR(omap->ehci_logic_fck))
		clk_prepare_enable(omap->ehci_logic_fck);

	for (i = 0; i < omap->nports; i++) {
		switch (pdata->port_mode[i]) {
		case OMAP_EHCI_PORT_MODE_HSIC:
			if (!IS_ERR(omap->hsic60m_clk[i])) {
				r = clk_prepare_enable(omap->hsic60m_clk[i]);
				if (r) {
					dev_err(dev,
					 "Can't enable port %d hsic60m clk:%d\n",
					 i, r);
				}
			}

			if (!IS_ERR(omap->hsic480m_clk[i])) {
				r = clk_prepare_enable(omap->hsic480m_clk[i]);
				if (r) {
					dev_err(dev,
					 "Can't enable port %d hsic480m clk:%d\n",
					 i, r);
				}
			}
		/* Fall through - as HSIC mode needs utmi_clk */

		case OMAP_EHCI_PORT_MODE_TLL:
			if (!IS_ERR(omap->utmi_clk[i])) {
				r = clk_prepare_enable(omap->utmi_clk[i]);
				if (r) {
					dev_err(dev,
					 "Can't enable port %d clk : %d\n",
					 i, r);
				}
			}
			break;
		default:
			break;
		}
	}

	return 0;
}
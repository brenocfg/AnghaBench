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
struct usbhs_omap_platform_data {int /*<<< orphan*/ * port_mode; } ;
struct usbhs_hcd_omap {int nports; struct usbhs_omap_platform_data* pdata; } ;

/* Variables and functions */
 int OMAP4_P1_MODE_CLEAR ; 
 int OMAP4_P1_MODE_HSIC ; 
 int OMAP4_P1_MODE_TLL ; 
 scalar_t__ is_ehci_hsic_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ehci_tll_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ohci_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned omap_usbhs_rev2_hostconfig(struct usbhs_hcd_omap *omap,
						unsigned reg)
{
	struct usbhs_omap_platform_data	*pdata = omap->pdata;
	int i;

	for (i = 0; i < omap->nports; i++) {
		/* Clear port mode fields for PHY mode */
		reg &= ~(OMAP4_P1_MODE_CLEAR << 2 * i);

		if (is_ehci_tll_mode(pdata->port_mode[i]) ||
				(is_ohci_port(pdata->port_mode[i])))
			reg |= OMAP4_P1_MODE_TLL << 2 * i;
		else if (is_ehci_hsic_mode(pdata->port_mode[i]))
			reg |= OMAP4_P1_MODE_HSIC << 2 * i;
	}

	return reg;
}
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
struct usbhs_omap_platform_data {int* port_mode; scalar_t__ single_ulpi_bypass; } ;
struct usbhs_hcd_omap {int nports; struct usbhs_omap_platform_data* pdata; } ;

/* Variables and functions */
#define  OMAP_EHCI_PORT_MODE_PHY 129 
 int OMAP_UHH_HOSTCONFIG_P1_CONNECT_STATUS ; 
 unsigned int OMAP_UHH_HOSTCONFIG_ULPI_BYPASS ; 
 unsigned int OMAP_UHH_HOSTCONFIG_ULPI_P1_BYPASS ; 
 int OMAP_UHH_HOSTCONFIG_ULPI_P2_BYPASS ; 
#define  OMAP_USBHS_PORT_MODE_UNUSED 128 
 scalar_t__ is_ehci_phy_mode (int) ; 

__attribute__((used)) static unsigned omap_usbhs_rev1_hostconfig(struct usbhs_hcd_omap *omap,
						unsigned reg)
{
	struct usbhs_omap_platform_data	*pdata = omap->pdata;
	int i;

	for (i = 0; i < omap->nports; i++) {
		switch (pdata->port_mode[i]) {
		case OMAP_USBHS_PORT_MODE_UNUSED:
			reg &= ~(OMAP_UHH_HOSTCONFIG_P1_CONNECT_STATUS << i);
			break;
		case OMAP_EHCI_PORT_MODE_PHY:
			if (pdata->single_ulpi_bypass)
				break;

			if (i == 0)
				reg &= ~OMAP_UHH_HOSTCONFIG_ULPI_P1_BYPASS;
			else
				reg &= ~(OMAP_UHH_HOSTCONFIG_ULPI_P2_BYPASS
								<< (i-1));
			break;
		default:
			if (pdata->single_ulpi_bypass)
				break;

			if (i == 0)
				reg |= OMAP_UHH_HOSTCONFIG_ULPI_P1_BYPASS;
			else
				reg |= OMAP_UHH_HOSTCONFIG_ULPI_P2_BYPASS
								<< (i-1);
			break;
		}
	}

	if (pdata->single_ulpi_bypass) {
		/* bypass ULPI only if none of the ports use PHY mode */
		reg |= OMAP_UHH_HOSTCONFIG_ULPI_BYPASS;

		for (i = 0; i < omap->nports; i++) {
			if (is_ehci_phy_mode(pdata->port_mode[i])) {
				reg &= ~OMAP_UHH_HOSTCONFIG_ULPI_BYPASS;
				break;
			}
		}
	}

	return reg;
}
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
typedef  enum usbhs_omap_port_mode { ____Placeholder_usbhs_omap_port_mode } usbhs_omap_port_mode ;

/* Variables and functions */
#define  OMAP_OHCI_PORT_MODE_PHY_3PIN_DATSE0 138 
#define  OMAP_OHCI_PORT_MODE_PHY_4PIN_DPDM 137 
#define  OMAP_OHCI_PORT_MODE_PHY_6PIN_DATSE0 136 
#define  OMAP_OHCI_PORT_MODE_PHY_6PIN_DPDM 135 
#define  OMAP_OHCI_PORT_MODE_TLL_2PIN_DATSE0 134 
#define  OMAP_OHCI_PORT_MODE_TLL_2PIN_DPDM 133 
#define  OMAP_OHCI_PORT_MODE_TLL_3PIN_DATSE0 132 
#define  OMAP_OHCI_PORT_MODE_TLL_4PIN_DPDM 131 
#define  OMAP_OHCI_PORT_MODE_TLL_6PIN_DATSE0 130 
#define  OMAP_OHCI_PORT_MODE_TLL_6PIN_DPDM 129 
 int OMAP_TLL_FSLSMODE_2PIN_DAT_DP_DM ; 
 int OMAP_TLL_FSLSMODE_2PIN_TLL_DAT_SE0 ; 
 int OMAP_TLL_FSLSMODE_3PIN_PHY ; 
 int OMAP_TLL_FSLSMODE_3PIN_TLL ; 
 int OMAP_TLL_FSLSMODE_4PIN_PHY ; 
 int OMAP_TLL_FSLSMODE_4PIN_TLL ; 
 int OMAP_TLL_FSLSMODE_6PIN_PHY_DAT_SE0 ; 
 int OMAP_TLL_FSLSMODE_6PIN_PHY_DP_DM ; 
 int OMAP_TLL_FSLSMODE_6PIN_TLL_DAT_SE0 ; 
 int OMAP_TLL_FSLSMODE_6PIN_TLL_DP_DM ; 
#define  OMAP_USBHS_PORT_MODE_UNUSED 128 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static unsigned ohci_omap3_fslsmode(enum usbhs_omap_port_mode mode)
{
	switch (mode) {
	case OMAP_USBHS_PORT_MODE_UNUSED:
	case OMAP_OHCI_PORT_MODE_PHY_6PIN_DATSE0:
		return OMAP_TLL_FSLSMODE_6PIN_PHY_DAT_SE0;

	case OMAP_OHCI_PORT_MODE_PHY_6PIN_DPDM:
		return OMAP_TLL_FSLSMODE_6PIN_PHY_DP_DM;

	case OMAP_OHCI_PORT_MODE_PHY_3PIN_DATSE0:
		return OMAP_TLL_FSLSMODE_3PIN_PHY;

	case OMAP_OHCI_PORT_MODE_PHY_4PIN_DPDM:
		return OMAP_TLL_FSLSMODE_4PIN_PHY;

	case OMAP_OHCI_PORT_MODE_TLL_6PIN_DATSE0:
		return OMAP_TLL_FSLSMODE_6PIN_TLL_DAT_SE0;

	case OMAP_OHCI_PORT_MODE_TLL_6PIN_DPDM:
		return OMAP_TLL_FSLSMODE_6PIN_TLL_DP_DM;

	case OMAP_OHCI_PORT_MODE_TLL_3PIN_DATSE0:
		return OMAP_TLL_FSLSMODE_3PIN_TLL;

	case OMAP_OHCI_PORT_MODE_TLL_4PIN_DPDM:
		return OMAP_TLL_FSLSMODE_4PIN_TLL;

	case OMAP_OHCI_PORT_MODE_TLL_2PIN_DATSE0:
		return OMAP_TLL_FSLSMODE_2PIN_TLL_DAT_SE0;

	case OMAP_OHCI_PORT_MODE_TLL_2PIN_DPDM:
		return OMAP_TLL_FSLSMODE_2PIN_DAT_DP_DM;
	default:
		pr_warn("Invalid port mode, using default\n");
		return OMAP_TLL_FSLSMODE_6PIN_PHY_DAT_SE0;
	}
}
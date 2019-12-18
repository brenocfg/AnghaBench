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
#define  OMAP_OHCI_PORT_MODE_PHY_3PIN_DATSE0 137 
#define  OMAP_OHCI_PORT_MODE_PHY_4PIN_DPDM 136 
#define  OMAP_OHCI_PORT_MODE_PHY_6PIN_DATSE0 135 
#define  OMAP_OHCI_PORT_MODE_PHY_6PIN_DPDM 134 
#define  OMAP_OHCI_PORT_MODE_TLL_2PIN_DATSE0 133 
#define  OMAP_OHCI_PORT_MODE_TLL_2PIN_DPDM 132 
#define  OMAP_OHCI_PORT_MODE_TLL_3PIN_DATSE0 131 
#define  OMAP_OHCI_PORT_MODE_TLL_4PIN_DPDM 130 
#define  OMAP_OHCI_PORT_MODE_TLL_6PIN_DATSE0 129 
#define  OMAP_OHCI_PORT_MODE_TLL_6PIN_DPDM 128 

__attribute__((used)) static bool is_ohci_port(enum usbhs_omap_port_mode pmode)
{
	switch (pmode) {
	case OMAP_OHCI_PORT_MODE_PHY_6PIN_DATSE0:
	case OMAP_OHCI_PORT_MODE_PHY_6PIN_DPDM:
	case OMAP_OHCI_PORT_MODE_PHY_3PIN_DATSE0:
	case OMAP_OHCI_PORT_MODE_PHY_4PIN_DPDM:
	case OMAP_OHCI_PORT_MODE_TLL_6PIN_DATSE0:
	case OMAP_OHCI_PORT_MODE_TLL_6PIN_DPDM:
	case OMAP_OHCI_PORT_MODE_TLL_3PIN_DATSE0:
	case OMAP_OHCI_PORT_MODE_TLL_4PIN_DPDM:
	case OMAP_OHCI_PORT_MODE_TLL_2PIN_DATSE0:
	case OMAP_OHCI_PORT_MODE_TLL_2PIN_DPDM:
		return true;

	default:
		return false;
	}
}
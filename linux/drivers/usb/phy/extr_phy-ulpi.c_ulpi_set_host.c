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
struct usb_phy {int flags; } ;
struct usb_otg {struct usb_bus* host; struct usb_phy* usb_phy; } ;
struct usb_bus {int dummy; } ;

/* Variables and functions */
 int ULPI_IC_3PIN_SERIAL ; 
 int ULPI_IC_6PIN_SERIAL ; 
 int ULPI_IC_CARKIT ; 
 int /*<<< orphan*/  ULPI_IFC_CTRL ; 
 unsigned int ULPI_IFC_CTRL_3_PIN_SERIAL_MODE ; 
 unsigned int ULPI_IFC_CTRL_6_PIN_SERIAL_MODE ; 
 unsigned int ULPI_IFC_CTRL_CARKITMODE ; 
 unsigned int usb_phy_io_read (struct usb_phy*,int /*<<< orphan*/ ) ; 
 int usb_phy_io_write (struct usb_phy*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ulpi_set_host(struct usb_otg *otg, struct usb_bus *host)
{
	struct usb_phy *phy = otg->usb_phy;
	unsigned int flags = usb_phy_io_read(phy, ULPI_IFC_CTRL);

	if (!host) {
		otg->host = NULL;
		return 0;
	}

	otg->host = host;

	flags &= ~(ULPI_IFC_CTRL_6_PIN_SERIAL_MODE |
		   ULPI_IFC_CTRL_3_PIN_SERIAL_MODE |
		   ULPI_IFC_CTRL_CARKITMODE);

	if (phy->flags & ULPI_IC_6PIN_SERIAL)
		flags |= ULPI_IFC_CTRL_6_PIN_SERIAL_MODE;
	else if (phy->flags & ULPI_IC_3PIN_SERIAL)
		flags |= ULPI_IFC_CTRL_3_PIN_SERIAL_MODE;
	else if (phy->flags & ULPI_IC_CARKIT)
		flags |= ULPI_IFC_CTRL_CARKITMODE;

	return usb_phy_io_write(phy, flags, ULPI_IFC_CTRL);
}
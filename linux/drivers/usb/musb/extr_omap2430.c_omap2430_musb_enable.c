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
typedef  int u8 ;
struct omap_musb_board_data {int /*<<< orphan*/  interface_type; } ;
struct omap2430_glue {int status; int /*<<< orphan*/  control_otghs; } ;
struct musb_hdrc_platform_data {struct omap_musb_board_data* board_data; } ;
struct musb {int /*<<< orphan*/  mregs; struct device* controller; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int MUSB_DEVCTL_BDEVICE ; 
 int MUSB_DEVCTL_SESSION ; 
#define  MUSB_ID_GROUND 129 
 int /*<<< orphan*/  MUSB_INTERFACE_UTMI ; 
#define  MUSB_VBUS_VALID 128 
 int /*<<< orphan*/  USB_MODE_DEVICE ; 
 int /*<<< orphan*/  USB_MODE_HOST ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct omap2430_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct musb_hdrc_platform_data* dev_get_platdata (struct device*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_control_usb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void omap2430_musb_enable(struct musb *musb)
{
	u8		devctl;
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);
	struct device *dev = musb->controller;
	struct omap2430_glue *glue = dev_get_drvdata(dev->parent);
	struct musb_hdrc_platform_data *pdata = dev_get_platdata(dev);
	struct omap_musb_board_data *data = pdata->board_data;


	switch (glue->status) {

	case MUSB_ID_GROUND:
		omap_control_usb_set_mode(glue->control_otghs, USB_MODE_HOST);
		if (data->interface_type != MUSB_INTERFACE_UTMI)
			break;
		devctl = musb_readb(musb->mregs, MUSB_DEVCTL);
		/* start the session */
		devctl |= MUSB_DEVCTL_SESSION;
		musb_writeb(musb->mregs, MUSB_DEVCTL, devctl);
		while (musb_readb(musb->mregs, MUSB_DEVCTL) &
				MUSB_DEVCTL_BDEVICE) {
			cpu_relax();

			if (time_after(jiffies, timeout)) {
				dev_err(dev, "configured as A device timeout");
				break;
			}
		}
		break;

	case MUSB_VBUS_VALID:
		omap_control_usb_set_mode(glue->control_otghs, USB_MODE_DEVICE);
		break;

	default:
		break;
	}
}
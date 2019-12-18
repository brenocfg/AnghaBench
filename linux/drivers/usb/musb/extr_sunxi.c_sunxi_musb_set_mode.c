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
typedef  int u8 ;
struct sunxi_glue {int phy_mode; int /*<<< orphan*/  work; int /*<<< orphan*/  flags; } ;
struct musb {int const port_mode; int port1_status; TYPE_1__* controller; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MUSB_HOST 130 
#define  MUSB_OTG 129 
#define  MUSB_PERIPHERAL 128 
 int PHY_MODE_USB_DEVICE ; 
 int PHY_MODE_USB_HOST ; 
 int PHY_MODE_USB_OTG ; 
 int /*<<< orphan*/  SUNXI_MUSB_FL_PHY_MODE_PEND ; 
 int USB_PORT_STAT_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sunxi_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_root_disconnect (struct musb*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sunxi_musb_set_mode(struct musb *musb, u8 mode)
{
	struct sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);
	enum phy_mode new_mode;

	switch (mode) {
	case MUSB_HOST:
		new_mode = PHY_MODE_USB_HOST;
		break;
	case MUSB_PERIPHERAL:
		new_mode = PHY_MODE_USB_DEVICE;
		break;
	case MUSB_OTG:
		new_mode = PHY_MODE_USB_OTG;
		break;
	default:
		dev_err(musb->controller->parent,
			"Error requested mode not supported by this kernel\n");
		return -EINVAL;
	}

	if (glue->phy_mode == new_mode)
		return 0;

	if (musb->port_mode != MUSB_OTG) {
		dev_err(musb->controller->parent,
			"Error changing modes is only supported in dual role mode\n");
		return -EINVAL;
	}

	if (musb->port1_status & USB_PORT_STAT_ENABLE)
		musb_root_disconnect(musb);

	/*
	 * phy_set_mode may sleep, and we're called with a spinlock held,
	 * so let sunxi_musb_work deal with it.
	 */
	glue->phy_mode = new_mode;
	set_bit(SUNXI_MUSB_FL_PHY_MODE_PEND, &glue->flags);
	schedule_work(&glue->work);

	return 0;
}
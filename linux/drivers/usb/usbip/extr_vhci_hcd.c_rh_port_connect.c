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
typedef  int u32 ;
struct vhci_hcd {int* port_status; struct vhci* vhci; } ;
struct vhci_device {int rhport; } ;
struct vhci {int /*<<< orphan*/  lock; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
 int USB_PORT_FEAT_C_CONNECTION ; 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_HIGH_SPEED ; 
 int USB_PORT_STAT_LOW_SPEED ; 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_LOW 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_rh (char*,int) ; 
 struct vhci_hcd* vdev_to_vhci_hcd (struct vhci_device*) ; 
 int /*<<< orphan*/  vhci_hcd_to_hcd (struct vhci_hcd*) ; 

void rh_port_connect(struct vhci_device *vdev, enum usb_device_speed speed)
{
	struct vhci_hcd	*vhci_hcd = vdev_to_vhci_hcd(vdev);
	struct vhci *vhci = vhci_hcd->vhci;
	int		rhport = vdev->rhport;
	u32		status;
	unsigned long	flags;

	usbip_dbg_vhci_rh("rh_port_connect %d\n", rhport);

	spin_lock_irqsave(&vhci->lock, flags);

	status = vhci_hcd->port_status[rhport];

	status |= USB_PORT_STAT_CONNECTION | (1 << USB_PORT_FEAT_C_CONNECTION);

	switch (speed) {
	case USB_SPEED_HIGH:
		status |= USB_PORT_STAT_HIGH_SPEED;
		break;
	case USB_SPEED_LOW:
		status |= USB_PORT_STAT_LOW_SPEED;
		break;
	default:
		break;
	}

	vhci_hcd->port_status[rhport] = status;

	spin_unlock_irqrestore(&vhci->lock, flags);

	usb_hcd_poll_rh_status(vhci_hcd_to_hcd(vhci_hcd));
}
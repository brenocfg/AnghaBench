#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ntxq; int nrxq; } ;
struct brcmf_usbdev_info {TYPE_2__* rx_reqs; TYPE_1__ bus_pub; TYPE_3__* tx_reqs; scalar_t__ bulk_urb; scalar_t__ ctl_urb; } ;
struct TYPE_6__ {scalar_t__ urb; } ;
struct TYPE_5__ {scalar_t__ urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static void brcmf_cancel_all_urbs(struct brcmf_usbdev_info *devinfo)
{
	int i;

	if (devinfo->ctl_urb)
		usb_kill_urb(devinfo->ctl_urb);
	if (devinfo->bulk_urb)
		usb_kill_urb(devinfo->bulk_urb);
	if (devinfo->tx_reqs)
		for (i = 0; i < devinfo->bus_pub.ntxq; i++)
			usb_kill_urb(devinfo->tx_reqs[i].urb);
	if (devinfo->rx_reqs)
		for (i = 0; i < devinfo->bus_pub.nrxq; i++)
			usb_kill_urb(devinfo->rx_reqs[i].urb);
}
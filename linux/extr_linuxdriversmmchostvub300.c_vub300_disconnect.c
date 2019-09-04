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
struct vub300_mmc_host {int /*<<< orphan*/  kref; int /*<<< orphan*/ * interface; struct mmc_host* mmc; } ;
struct usb_interface {int dummy; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int interface_to_InterfaceNumber (struct usb_interface*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 struct vub300_mmc_host* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vub300_delete ; 

__attribute__((used)) static void vub300_disconnect(struct usb_interface *interface)
{				/* NOT irq */
	struct vub300_mmc_host *vub300 = usb_get_intfdata(interface);
	if (!vub300 || !vub300->mmc) {
		return;
	} else {
		struct mmc_host *mmc = vub300->mmc;
		if (!vub300->mmc) {
			return;
		} else {
			int ifnum = interface_to_InterfaceNumber(interface);
			usb_set_intfdata(interface, NULL);
			/* prevent more I/O from starting */
			vub300->interface = NULL;
			kref_put(&vub300->kref, vub300_delete);
			mmc_remove_host(mmc);
			pr_info("USB vub300 remote SDIO host controller[%d]"
				" now disconnected", ifnum);
			return;
		}
	}
}
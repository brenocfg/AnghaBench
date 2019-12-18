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
struct vub300_mmc_host {int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  errors; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vub300_mmc_host* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int vub300_post_reset(struct usb_interface *intf)
{				/* NOT irq */
	struct vub300_mmc_host *vub300 = usb_get_intfdata(intf);
	/* we are sure no URBs are active - no locking needed */
	vub300->errors = -EPIPE;
	mutex_unlock(&vub300->cmd_mutex);
	return 0;
}
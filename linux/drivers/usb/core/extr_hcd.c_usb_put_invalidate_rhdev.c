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
struct TYPE_2__ {struct usb_device* root_hub; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_port_peer_mutex ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static void usb_put_invalidate_rhdev(struct usb_hcd *hcd)
{
	struct usb_device *rhdev;

	mutex_lock(&usb_port_peer_mutex);
	rhdev = hcd->self.root_hub;
	hcd->self.root_hub = NULL;
	mutex_unlock(&usb_port_peer_mutex);
	usb_put_dev(rhdev);
}
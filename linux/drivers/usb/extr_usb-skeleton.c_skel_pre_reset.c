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
struct usb_skel {int /*<<< orphan*/  io_mutex; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skel_draw_down (struct usb_skel*) ; 
 struct usb_skel* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int skel_pre_reset(struct usb_interface *intf)
{
	struct usb_skel *dev = usb_get_intfdata(intf);

	mutex_lock(&dev->io_mutex);
	skel_draw_down(dev);

	return 0;
}
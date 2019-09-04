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
struct usb_interface {int dummy; } ;
struct cm109_dev {int /*<<< orphan*/  idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cm109_usb_cleanup (struct cm109_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 struct cm109_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cm109_usb_disconnect(struct usb_interface *interface)
{
	struct cm109_dev *dev = usb_get_intfdata(interface);

	usb_set_intfdata(interface, NULL);
	input_unregister_device(dev->idev);
	cm109_usb_cleanup(dev);
}
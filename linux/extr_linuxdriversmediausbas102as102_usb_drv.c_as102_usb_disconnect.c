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
struct as102_dev_t {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  as102_dvb_unregister (struct as102_dev_t*) ; 
 int /*<<< orphan*/  as102_free_usb_stream_buffer (struct as102_dev_t*) ; 
 int /*<<< orphan*/  as102_usb_class_driver ; 
 int /*<<< orphan*/  as102_usb_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct as102_dev_t* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void as102_usb_disconnect(struct usb_interface *intf)
{
	struct as102_dev_t *as102_dev;

	/* extract as102_dev_t from usb_device private data */
	as102_dev = usb_get_intfdata(intf);

	/* unregister dvb layer */
	as102_dvb_unregister(as102_dev);

	/* free usb buffers */
	as102_free_usb_stream_buffer(as102_dev);

	usb_set_intfdata(intf, NULL);

	/* usb unregister device */
	usb_deregister_dev(intf, &as102_usb_class_driver);

	/* decrement usage counter */
	kref_put(&as102_dev->kref, as102_usb_release);

	pr_info("%s: device has been disconnected\n", DRIVER_NAME);
}
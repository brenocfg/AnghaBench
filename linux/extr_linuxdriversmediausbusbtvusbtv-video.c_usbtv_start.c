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
struct usbtv {struct urb** isoc_urbs; int /*<<< orphan*/  udev; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USBTV_ISOC_TRANSFERS ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbtv_audio_resume (struct usbtv*) ; 
 int /*<<< orphan*/  usbtv_audio_suspend (struct usbtv*) ; 
 int usbtv_setup_capture (struct usbtv*) ; 
 struct urb* usbtv_setup_iso_transfer (struct usbtv*) ; 
 int /*<<< orphan*/  usbtv_stop (struct usbtv*) ; 

__attribute__((used)) static int usbtv_start(struct usbtv *usbtv)
{
	int i;
	int ret;

	usbtv_audio_suspend(usbtv);

	ret = usb_set_interface(usbtv->udev, 0, 0);
	if (ret < 0)
		return ret;

	ret = usbtv_setup_capture(usbtv);
	if (ret < 0)
		return ret;

	ret = usb_set_interface(usbtv->udev, 0, 1);
	if (ret < 0)
		return ret;

	usbtv_audio_resume(usbtv);

	for (i = 0; i < USBTV_ISOC_TRANSFERS; i++) {
		struct urb *ip;

		ip = usbtv_setup_iso_transfer(usbtv);
		if (ip == NULL) {
			ret = -ENOMEM;
			goto start_fail;
		}
		usbtv->isoc_urbs[i] = ip;

		ret = usb_submit_urb(ip, GFP_KERNEL);
		if (ret < 0)
			goto start_fail;
	}

	return 0;

start_fail:
	usbtv_stop(usbtv);
	return ret;
}
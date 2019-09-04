#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vub300_mmc_host {TYPE_1__* urb; struct usb_device* udev; } ;
struct usb_device {int dummy; } ;
struct completion {int dummy; } ;
struct TYPE_6__ {int actual_length; int status; struct completion* context; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_1__*,struct usb_device*,unsigned int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vub300_usb_bulk_msg_completion ; 
 int /*<<< orphan*/  wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vub300_usb_bulk_msg(struct vub300_mmc_host *vub300,
			       unsigned int pipe, void *data, int len,
			       int *actual_length, int timeout_msecs)
{
	/* cmd_mutex is held by vub300_cmndwork_thread */
	struct usb_device *usb_dev = vub300->udev;
	struct completion done;
	int retval;
	vub300->urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!vub300->urb)
		return -ENOMEM;
	usb_fill_bulk_urb(vub300->urb, usb_dev, pipe, data, len,
			  vub300_usb_bulk_msg_completion, NULL);
	init_completion(&done);
	vub300->urb->context = &done;
	vub300->urb->actual_length = 0;
	retval = usb_submit_urb(vub300->urb, GFP_KERNEL);
	if (unlikely(retval))
		goto out;
	if (!wait_for_completion_timeout
	    (&done, msecs_to_jiffies(timeout_msecs))) {
		retval = -ETIMEDOUT;
		usb_kill_urb(vub300->urb);
	} else {
		retval = vub300->urb->status;
	}
out:
	*actual_length = vub300->urb->actual_length;
	usb_free_urb(vub300->urb);
	vub300->urb = NULL;
	return retval;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbhid_device {int outhead; int outtail; int ctrlhead; int ctrltail; int /*<<< orphan*/  intf; int /*<<< orphan*/  iofl; scalar_t__ urbctrl; int /*<<< orphan*/  lock; scalar_t__ last_ctrl; TYPE_2__* ctrl; scalar_t__ urbout; scalar_t__ last_out; TYPE_1__* out; } ;
struct hid_report {scalar_t__ type; } ;
struct hid_device {int quirks; struct usbhid_device* driver_data; } ;
struct TYPE_4__ {unsigned char dir; struct hid_report* report; void* raw_report; } ;
struct TYPE_3__ {struct hid_report* report; void* raw_report; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HID_CONTROL_FIFO_SIZE ; 
 int /*<<< orphan*/  HID_CTRL_RUNNING ; 
 int /*<<< orphan*/  HID_DISCONNECTED ; 
 int HID_OUTPUT_FIFO_SIZE ; 
 scalar_t__ HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  HID_OUT_RUNNING ; 
 int HID_QUIRK_NOGET ; 
 int HZ ; 
 unsigned char USB_DIR_IN ; 
 unsigned char USB_DIR_OUT ; 
 void* hid_alloc_report_buf (struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_output_report (struct hid_report*,void*) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_autopm_get_interface_no_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_block_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_unblock_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_unlink_urb (scalar_t__) ; 
 int /*<<< orphan*/  usbhid_restart_ctrl_queue (struct usbhid_device*) ; 
 int /*<<< orphan*/  usbhid_restart_out_queue (struct usbhid_device*) ; 

__attribute__((used)) static void __usbhid_submit_report(struct hid_device *hid, struct hid_report *report,
				   unsigned char dir)
{
	int head;
	struct usbhid_device *usbhid = hid->driver_data;

	if (((hid->quirks & HID_QUIRK_NOGET) && dir == USB_DIR_IN) ||
		test_bit(HID_DISCONNECTED, &usbhid->iofl))
		return;

	if (usbhid->urbout && dir == USB_DIR_OUT && report->type == HID_OUTPUT_REPORT) {
		if ((head = (usbhid->outhead + 1) & (HID_OUTPUT_FIFO_SIZE - 1)) == usbhid->outtail) {
			hid_warn(hid, "output queue full\n");
			return;
		}

		usbhid->out[usbhid->outhead].raw_report = hid_alloc_report_buf(report, GFP_ATOMIC);
		if (!usbhid->out[usbhid->outhead].raw_report) {
			hid_warn(hid, "output queueing failed\n");
			return;
		}
		hid_output_report(report, usbhid->out[usbhid->outhead].raw_report);
		usbhid->out[usbhid->outhead].report = report;
		usbhid->outhead = head;

		/* If the queue isn't running, restart it */
		if (!test_bit(HID_OUT_RUNNING, &usbhid->iofl)) {
			usbhid_restart_out_queue(usbhid);

		/* Otherwise see if an earlier request has timed out */
		} else if (time_after(jiffies, usbhid->last_out + HZ * 5)) {

			/* Prevent autosuspend following the unlink */
			usb_autopm_get_interface_no_resume(usbhid->intf);

			/*
			 * Prevent resubmission in case the URB completes
			 * before we can unlink it.  We don't want to cancel
			 * the wrong transfer!
			 */
			usb_block_urb(usbhid->urbout);

			/* Drop lock to avoid deadlock if the callback runs */
			spin_unlock(&usbhid->lock);

			usb_unlink_urb(usbhid->urbout);
			spin_lock(&usbhid->lock);
			usb_unblock_urb(usbhid->urbout);

			/* Unlink might have stopped the queue */
			if (!test_bit(HID_OUT_RUNNING, &usbhid->iofl))
				usbhid_restart_out_queue(usbhid);

			/* Now we can allow autosuspend again */
			usb_autopm_put_interface_async(usbhid->intf);
		}
		return;
	}

	if ((head = (usbhid->ctrlhead + 1) & (HID_CONTROL_FIFO_SIZE - 1)) == usbhid->ctrltail) {
		hid_warn(hid, "control queue full\n");
		return;
	}

	if (dir == USB_DIR_OUT) {
		usbhid->ctrl[usbhid->ctrlhead].raw_report = hid_alloc_report_buf(report, GFP_ATOMIC);
		if (!usbhid->ctrl[usbhid->ctrlhead].raw_report) {
			hid_warn(hid, "control queueing failed\n");
			return;
		}
		hid_output_report(report, usbhid->ctrl[usbhid->ctrlhead].raw_report);
	}
	usbhid->ctrl[usbhid->ctrlhead].report = report;
	usbhid->ctrl[usbhid->ctrlhead].dir = dir;
	usbhid->ctrlhead = head;

	/* If the queue isn't running, restart it */
	if (!test_bit(HID_CTRL_RUNNING, &usbhid->iofl)) {
		usbhid_restart_ctrl_queue(usbhid);

	/* Otherwise see if an earlier request has timed out */
	} else if (time_after(jiffies, usbhid->last_ctrl + HZ * 5)) {

		/* Prevent autosuspend following the unlink */
		usb_autopm_get_interface_no_resume(usbhid->intf);

		/*
		 * Prevent resubmission in case the URB completes
		 * before we can unlink it.  We don't want to cancel
		 * the wrong transfer!
		 */
		usb_block_urb(usbhid->urbctrl);

		/* Drop lock to avoid deadlock if the callback runs */
		spin_unlock(&usbhid->lock);

		usb_unlink_urb(usbhid->urbctrl);
		spin_lock(&usbhid->lock);
		usb_unblock_urb(usbhid->urbctrl);

		/* Unlink might have stopped the queue */
		if (!test_bit(HID_CTRL_RUNNING, &usbhid->iofl))
			usbhid_restart_ctrl_queue(usbhid);

		/* Now we can allow autosuspend again */
		usb_autopm_put_interface_async(usbhid->intf);
	}
}
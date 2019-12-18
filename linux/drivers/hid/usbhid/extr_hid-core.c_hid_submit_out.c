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
struct usbhid_device {size_t outtail; int /*<<< orphan*/  last_out; TYPE_2__* urbout; TYPE_1__* out; int /*<<< orphan*/  outbuf; } ;
struct hid_report {int dummy; } ;
struct hid_device {struct usbhid_device* driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {char* raw_report; struct hid_report* report; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dbg_hid (char*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 int /*<<< orphan*/  hid_report_len (struct hid_report*) ; 
 int /*<<< orphan*/  hid_to_usb_dev (struct hid_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hid_submit_out(struct hid_device *hid)
{
	struct hid_report *report;
	char *raw_report;
	struct usbhid_device *usbhid = hid->driver_data;
	int r;

	report = usbhid->out[usbhid->outtail].report;
	raw_report = usbhid->out[usbhid->outtail].raw_report;

	usbhid->urbout->transfer_buffer_length = hid_report_len(report);
	usbhid->urbout->dev = hid_to_usb_dev(hid);
	if (raw_report) {
		memcpy(usbhid->outbuf, raw_report,
				usbhid->urbout->transfer_buffer_length);
		kfree(raw_report);
		usbhid->out[usbhid->outtail].raw_report = NULL;
	}

	dbg_hid("submitting out urb\n");

	r = usb_submit_urb(usbhid->urbout, GFP_ATOMIC);
	if (r < 0) {
		hid_err(hid, "usb_submit_urb(out) failed: %d\n", r);
		return r;
	}
	usbhid->last_out = jiffies;
	return 0;
}
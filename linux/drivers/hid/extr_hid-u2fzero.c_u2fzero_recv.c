#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct u2fzero_transfer_context {int /*<<< orphan*/  done; } ;
struct u2fzero_device {int /*<<< orphan*/  lock; struct u2f_hid_report* buf_in; TYPE_1__* urb; struct u2f_hid_msg* buf_out; struct hid_device* hdev; } ;
struct u2f_hid_report {int dummy; } ;
struct u2f_hid_msg {int dummy; } ;
struct hid_device {int dummy; } ;
struct TYPE_3__ {int actual_length; struct u2fzero_transfer_context* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,...) ; 
 int hid_hw_output_report (struct hid_device*,struct u2f_hid_msg*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct u2f_hid_msg*,struct u2f_hid_report*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u2fzero_recv(struct u2fzero_device *dev,
			struct u2f_hid_report *req,
			struct u2f_hid_msg *resp)
{
	int ret;
	struct hid_device *hdev = dev->hdev;
	struct u2fzero_transfer_context ctx;

	mutex_lock(&dev->lock);

	memcpy(dev->buf_out, req, sizeof(struct u2f_hid_report));

	dev->urb->context = &ctx;
	init_completion(&ctx.done);

	ret = usb_submit_urb(dev->urb, GFP_NOIO);
	if (unlikely(ret)) {
		hid_err(hdev, "usb_submit_urb failed: %d", ret);
		goto err;
	}

	ret = hid_hw_output_report(dev->hdev, dev->buf_out,
				   sizeof(struct u2f_hid_msg));

	if (ret < 0) {
		hid_err(hdev, "hid_hw_output_report failed: %d", ret);
		goto err;
	}

	ret = (wait_for_completion_timeout(
		&ctx.done, msecs_to_jiffies(USB_CTRL_SET_TIMEOUT)));
	if (ret < 0) {
		usb_kill_urb(dev->urb);
		hid_err(hdev, "urb submission timed out");
	} else {
		ret = dev->urb->actual_length;
		memcpy(resp, dev->buf_in, ret);
	}

err:
	mutex_unlock(&dev->lock);

	return ret;
}
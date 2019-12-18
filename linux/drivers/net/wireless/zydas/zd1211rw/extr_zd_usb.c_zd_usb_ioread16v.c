#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zd_addr_t ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  completion; } ;
struct TYPE_5__ {TYPE_1__ read_regs; } ;
struct zd_usb {TYPE_2__ intr; scalar_t__ req_buf; } ;
struct usb_req_read_regs {void** addr; void* id; } ;
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 unsigned int USB_MAX_IOREAD16_COUNT ; 
 int /*<<< orphan*/  USB_REQ_READ_REGS ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  disable_read_regs_int (struct zd_usb*) ; 
 int get_results (struct zd_usb*,int /*<<< orphan*/ *,struct usb_req_read_regs*,unsigned int,int*) ; 
 scalar_t__ in_atomic () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_read_regs_int (struct zd_usb*,struct usb_req_read_regs*,unsigned int) ; 
 int /*<<< orphan*/  usb_int_enabled (struct zd_usb*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zd_ep_regs_out_msg (struct usb_device*,struct usb_req_read_regs*,int,int*,int) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 TYPE_3__* zd_usb_to_chip (struct zd_usb*) ; 
 struct usb_device* zd_usb_to_usbdev (struct zd_usb*) ; 

int zd_usb_ioread16v(struct zd_usb *usb, u16 *values,
	             const zd_addr_t *addresses, unsigned int count)
{
	int r, i, req_len, actual_req_len, try_count = 0;
	struct usb_device *udev;
	struct usb_req_read_regs *req = NULL;
	unsigned long timeout;
	bool retry = false;

	if (count < 1) {
		dev_dbg_f(zd_usb_dev(usb), "error: count is zero\n");
		return -EINVAL;
	}
	if (count > USB_MAX_IOREAD16_COUNT) {
		dev_dbg_f(zd_usb_dev(usb),
			 "error: count %u exceeds possible max %u\n",
			 count, USB_MAX_IOREAD16_COUNT);
		return -EINVAL;
	}
	if (in_atomic()) {
		dev_dbg_f(zd_usb_dev(usb),
			 "error: io in atomic context not supported\n");
		return -EWOULDBLOCK;
	}
	if (!usb_int_enabled(usb)) {
		dev_dbg_f(zd_usb_dev(usb),
			  "error: usb interrupt not enabled\n");
		return -EWOULDBLOCK;
	}

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));
	BUILD_BUG_ON(sizeof(struct usb_req_read_regs) + USB_MAX_IOREAD16_COUNT *
		     sizeof(__le16) > sizeof(usb->req_buf));
	BUG_ON(sizeof(struct usb_req_read_regs) + count * sizeof(__le16) >
	       sizeof(usb->req_buf));

	req_len = sizeof(struct usb_req_read_regs) + count * sizeof(__le16);
	req = (void *)usb->req_buf;

	req->id = cpu_to_le16(USB_REQ_READ_REGS);
	for (i = 0; i < count; i++)
		req->addr[i] = cpu_to_le16((u16)addresses[i]);

retry_read:
	try_count++;
	udev = zd_usb_to_usbdev(usb);
	prepare_read_regs_int(usb, req, count);
	r = zd_ep_regs_out_msg(udev, req, req_len, &actual_req_len, 50 /*ms*/);
	if (r) {
		dev_dbg_f(zd_usb_dev(usb),
			"error in zd_ep_regs_out_msg(). Error number %d\n", r);
		goto error;
	}
	if (req_len != actual_req_len) {
		dev_dbg_f(zd_usb_dev(usb), "error in zd_ep_regs_out_msg()\n"
			" req_len %d != actual_req_len %d\n",
			req_len, actual_req_len);
		r = -EIO;
		goto error;
	}

	timeout = wait_for_completion_timeout(&usb->intr.read_regs.completion,
					      msecs_to_jiffies(50));
	if (!timeout) {
		disable_read_regs_int(usb);
		dev_dbg_f(zd_usb_dev(usb), "read timed out\n");
		r = -ETIMEDOUT;
		goto error;
	}

	r = get_results(usb, values, req, count, &retry);
	if (retry && try_count < 20) {
		dev_dbg_f(zd_usb_dev(usb), "read retry, tries so far: %d\n",
				try_count);
		goto retry_read;
	}
error:
	return r;
}
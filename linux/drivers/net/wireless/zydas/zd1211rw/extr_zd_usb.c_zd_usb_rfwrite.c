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
typedef  unsigned long u8 ;
typedef  unsigned long u32 ;
typedef  unsigned long u16 ;
struct zd_usb {scalar_t__ req_buf; } ;
struct usb_req_rfwrite {void** bit_values; void* bits; void* value; void* id; } ;
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int EIO ; 
 int EWOULDBLOCK ; 
 unsigned long RF_CLK ; 
 unsigned long RF_DATA ; 
 unsigned long RF_IF_LE ; 
 unsigned long USB_MAX_RFWRITE_BIT_COUNT ; 
 unsigned long USB_MIN_RFWRITE_BIT_COUNT ; 
 unsigned long USB_REQ_WRITE_RF ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZD_CR203 ; 
 void* cpu_to_le16 (unsigned long) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ in_atomic () ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int zd_ep_regs_out_msg (struct usb_device*,struct usb_req_rfwrite*,int,int*,int) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 int zd_usb_ioread16 (struct zd_usb*,unsigned long*,int /*<<< orphan*/ ) ; 
 TYPE_1__* zd_usb_to_chip (struct zd_usb*) ; 
 struct usb_device* zd_usb_to_usbdev (struct zd_usb*) ; 

int zd_usb_rfwrite(struct zd_usb *usb, u32 value, u8 bits)
{
	int r;
	struct usb_device *udev;
	struct usb_req_rfwrite *req = NULL;
	int i, req_len, actual_req_len;
	u16 bit_value_template;

	if (in_atomic()) {
		dev_dbg_f(zd_usb_dev(usb),
			"error: io in atomic context not supported\n");
		return -EWOULDBLOCK;
	}
	if (bits < USB_MIN_RFWRITE_BIT_COUNT) {
		dev_dbg_f(zd_usb_dev(usb),
			"error: bits %d are smaller than"
			" USB_MIN_RFWRITE_BIT_COUNT %d\n",
			bits, USB_MIN_RFWRITE_BIT_COUNT);
		return -EINVAL;
	}
	if (bits > USB_MAX_RFWRITE_BIT_COUNT) {
		dev_dbg_f(zd_usb_dev(usb),
			"error: bits %d exceed USB_MAX_RFWRITE_BIT_COUNT %d\n",
			bits, USB_MAX_RFWRITE_BIT_COUNT);
		return -EINVAL;
	}
#ifdef DEBUG
	if (value & (~0UL << bits)) {
		dev_dbg_f(zd_usb_dev(usb),
			"error: value %#09x has bits >= %d set\n",
			value, bits);
		return -EINVAL;
	}
#endif /* DEBUG */

	dev_dbg_f(zd_usb_dev(usb), "value %#09x bits %d\n", value, bits);

	r = zd_usb_ioread16(usb, &bit_value_template, ZD_CR203);
	if (r) {
		dev_dbg_f(zd_usb_dev(usb),
			"error %d: Couldn't read ZD_CR203\n", r);
		return r;
	}
	bit_value_template &= ~(RF_IF_LE|RF_CLK|RF_DATA);

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));
	BUILD_BUG_ON(sizeof(struct usb_req_rfwrite) +
		     USB_MAX_RFWRITE_BIT_COUNT * sizeof(__le16) >
		     sizeof(usb->req_buf));
	BUG_ON(sizeof(struct usb_req_rfwrite) + bits * sizeof(__le16) >
	       sizeof(usb->req_buf));

	req_len = sizeof(struct usb_req_rfwrite) + bits * sizeof(__le16);
	req = (void *)usb->req_buf;

	req->id = cpu_to_le16(USB_REQ_WRITE_RF);
	/* 1: 3683a, but not used in ZYDAS driver */
	req->value = cpu_to_le16(2);
	req->bits = cpu_to_le16(bits);

	for (i = 0; i < bits; i++) {
		u16 bv = bit_value_template;
		if (value & (1 << (bits-1-i)))
			bv |= RF_DATA;
		req->bit_values[i] = cpu_to_le16(bv);
	}

	udev = zd_usb_to_usbdev(usb);
	r = zd_ep_regs_out_msg(udev, req, req_len, &actual_req_len, 50 /*ms*/);
	if (r) {
		dev_dbg_f(zd_usb_dev(usb),
			"error in zd_ep_regs_out_msg(). Error number %d\n", r);
		goto out;
	}
	if (req_len != actual_req_len) {
		dev_dbg_f(zd_usb_dev(usb), "error in zd_ep_regs_out_msg()"
			" req_len %d != actual_req_len %d\n",
			req_len, actual_req_len);
		r = -EIO;
		goto out;
	}

	/* FALL-THROUGH with r == 0 */
out:
	return r;
}
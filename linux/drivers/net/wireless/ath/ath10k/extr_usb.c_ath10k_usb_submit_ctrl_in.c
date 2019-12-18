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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath10k_usb {int /*<<< orphan*/  udev; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 struct ath10k_usb* ath10k_usb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_usb_submit_ctrl_in(struct ath10k *ar,
				     u8 req, u16 value, u16 index, void *data,
				     u32 size)
{
	struct ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	u8 *buf = NULL;
	int ret;

	if (size > 0) {
		buf = kmalloc(size, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
	}

	/* note: if successful returns number of bytes transferred */
	ret = usb_control_msg(ar_usb->udev,
			      usb_rcvctrlpipe(ar_usb->udev, 0),
			      req,
			      USB_DIR_IN | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, value, index, buf,
			      size, 2 * HZ);

	if (ret < 0) {
		ath10k_warn(ar, "Failed to read usb control message: %d\n",
			    ret);
		kfree(buf);
		return ret;
	}

	memcpy((u8 *)data, buf, size);

	kfree(buf);

	return 0;
}
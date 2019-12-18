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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DRCI_READ_REQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int drci_rd_reg(struct usb_device *dev, u16 reg, u16 *buf)
{
	int retval;
	__le16 *dma_buf = kzalloc(sizeof(*dma_buf), GFP_KERNEL);
	u8 req_type = USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE;

	if (!dma_buf)
		return -ENOMEM;

	retval = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
				 DRCI_READ_REQ, req_type,
				 0x0000,
				 reg, dma_buf, sizeof(*dma_buf), 5 * HZ);
	*buf = le16_to_cpu(*dma_buf);
	kfree(dma_buf);

	return retval;
}
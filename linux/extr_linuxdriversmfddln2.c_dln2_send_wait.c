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
typedef  int /*<<< orphan*/  u16 ;
struct dln2_dev {int /*<<< orphan*/  ep_out; int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_USB_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dln2_prep_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_send_wait(struct dln2_dev *dln2, u16 handle, u16 cmd, u16 echo,
			  const void *obuf, int obuf_len)
{
	int ret = 0;
	int len = obuf_len;
	void *buf;
	int actual;

	buf = dln2_prep_buf(handle, cmd, echo, obuf, &len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = usb_bulk_msg(dln2->usb_dev,
			   usb_sndbulkpipe(dln2->usb_dev, dln2->ep_out),
			   buf, len, &actual, DLN2_USB_TIMEOUT);

	kfree(buf);

	return ret;
}
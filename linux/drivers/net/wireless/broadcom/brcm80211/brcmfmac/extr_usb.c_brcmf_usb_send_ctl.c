#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_complete_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  wLength; } ;
struct brcmf_usbdev_info {TYPE_2__* ctl_urb; TYPE_1__ ctl_write; int /*<<< orphan*/  ctl_out_pipe; int /*<<< orphan*/  usbdev; scalar_t__ ctl_urb_actual_length; scalar_t__ ctl_urb_status; } ;
struct TYPE_5__ {int transfer_buffer_length; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 scalar_t__ brcmf_usb_ctlwrite_complete ; 
 int /*<<< orphan*/  cpu_to_le16p (int*) ; 
 int /*<<< orphan*/  usb_fill_control_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct brcmf_usbdev_info*) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
brcmf_usb_send_ctl(struct brcmf_usbdev_info *devinfo, u8 *buf, int len)
{
	int ret;
	u16 size;

	brcmf_dbg(USB, "Enter\n");
	if (devinfo == NULL || buf == NULL ||
	    len == 0 || devinfo->ctl_urb == NULL)
		return -EINVAL;

	size = len;
	devinfo->ctl_write.wLength = cpu_to_le16p(&size);
	devinfo->ctl_urb->transfer_buffer_length = size;
	devinfo->ctl_urb_status = 0;
	devinfo->ctl_urb_actual_length = 0;

	usb_fill_control_urb(devinfo->ctl_urb,
		devinfo->usbdev,
		devinfo->ctl_out_pipe,
		(unsigned char *) &devinfo->ctl_write,
		buf, size,
		(usb_complete_t)brcmf_usb_ctlwrite_complete,
		devinfo);

	ret = usb_submit_urb(devinfo->ctl_urb, GFP_ATOMIC);
	if (ret < 0)
		brcmf_err("usb_submit_urb failed %d\n", ret);

	return ret;
}
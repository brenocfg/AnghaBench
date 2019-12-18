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
struct usbdux_private {int /*<<< orphan*/ * insn_buf; } ;
struct usb_device {int dummy; } ;
struct comedi_device {struct usbdux_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_TIMEOUT ; 
 int EFAULT ; 
 int RETRIES ; 
 int /*<<< orphan*/  SIZEINSNBUF ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int receive_dux_commands(struct comedi_device *dev, unsigned int command)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct usbdux_private *devpriv = dev->private;
	int ret;
	int nrec;
	int i;

	for (i = 0; i < RETRIES; i++) {
		ret = usb_bulk_msg(usb, usb_rcvbulkpipe(usb, 8),
				   devpriv->insn_buf, SIZEINSNBUF,
				   &nrec, BULK_TIMEOUT);
		if (ret < 0)
			return ret;
		if (le16_to_cpu(devpriv->insn_buf[0]) == command)
			return ret;
	}
	/* command not received */
	return -EFAULT;
}
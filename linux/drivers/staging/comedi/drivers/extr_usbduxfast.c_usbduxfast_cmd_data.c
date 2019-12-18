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
typedef  void* u8 ;
struct usbduxfast_private {void** duxbuf; } ;
struct comedi_device {struct usbduxfast_private* private; } ;

/* Variables and functions */

__attribute__((used)) static void usbduxfast_cmd_data(struct comedi_device *dev, int index,
				u8 len, u8 op, u8 out, u8 log)
{
	struct usbduxfast_private *devpriv = dev->private;

	/* Set the GPIF bytes, the first byte is the command byte */
	devpriv->duxbuf[1 + 0x00 + index] = len;
	devpriv->duxbuf[1 + 0x08 + index] = op;
	devpriv->duxbuf[1 + 0x10 + index] = out;
	devpriv->duxbuf[1 + 0x18 + index] = log;
}
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
struct vmk80xx_private {int /*<<< orphan*/  usb_tx_buf; int /*<<< orphan*/  ep_tx; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMK8055_CMD_RST ; 
 int /*<<< orphan*/  VMK8055_CMD_WRT_AD ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t usb_endpoint_maxp (int /*<<< orphan*/ ) ; 
 int vmk80xx_write_packet (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmk80xx_reset_device(struct comedi_device *dev)
{
	struct vmk80xx_private *devpriv = dev->private;
	size_t size;
	int retval;

	size = usb_endpoint_maxp(devpriv->ep_tx);
	memset(devpriv->usb_tx_buf, 0, size);
	retval = vmk80xx_write_packet(dev, VMK8055_CMD_RST);
	if (retval)
		return retval;
	/* set outputs to known state as we cannot read them */
	return vmk80xx_write_packet(dev, VMK8055_CMD_WRT_AD);
}
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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct ch341_private {int /*<<< orphan*/  mcr; int /*<<< orphan*/  lcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH341_REQ_READ_VERSION ; 
 int /*<<< orphan*/  CH341_REQ_SERIAL_INIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ch341_control_in (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int const) ; 
 int ch341_control_out (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ch341_set_baudrate_lcr (struct usb_device*,struct ch341_private*,int /*<<< orphan*/ ) ; 
 int ch341_set_handshake (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ch341_configure(struct usb_device *dev, struct ch341_private *priv)
{
	const unsigned int size = 2;
	char *buffer;
	int r;

	buffer = kmalloc(size, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	/* expect two bytes 0x27 0x00 */
	r = ch341_control_in(dev, CH341_REQ_READ_VERSION, 0, 0, buffer, size);
	if (r < 0)
		goto out;
	dev_dbg(&dev->dev, "Chip version: 0x%02x\n", buffer[0]);

	r = ch341_control_out(dev, CH341_REQ_SERIAL_INIT, 0, 0);
	if (r < 0)
		goto out;

	r = ch341_set_baudrate_lcr(dev, priv, priv->lcr);
	if (r < 0)
		goto out;

	r = ch341_set_handshake(dev, priv->mcr);

out:	kfree(buffer);
	return r;
}
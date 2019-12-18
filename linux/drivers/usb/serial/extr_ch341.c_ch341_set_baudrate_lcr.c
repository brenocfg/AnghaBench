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
typedef  short u8 ;
struct usb_device {int dummy; } ;
struct ch341_private {unsigned long baud_rate; } ;

/* Variables and functions */
 short BIT (int) ; 
 short CH341_BAUDBASE_DIVMAX ; 
 unsigned long CH341_BAUDBASE_FACTOR ; 
 int /*<<< orphan*/  CH341_REQ_WRITE_REG ; 
 int EINVAL ; 
 int ch341_control_out (struct usb_device*,int /*<<< orphan*/ ,int,short) ; 

__attribute__((used)) static int ch341_set_baudrate_lcr(struct usb_device *dev,
				  struct ch341_private *priv, u8 lcr)
{
	short a;
	int r;
	unsigned long factor;
	short divisor;

	if (!priv->baud_rate)
		return -EINVAL;
	factor = (CH341_BAUDBASE_FACTOR / priv->baud_rate);
	divisor = CH341_BAUDBASE_DIVMAX;

	while ((factor > 0xfff0) && divisor) {
		factor >>= 3;
		divisor--;
	}

	if (factor > 0xfff0)
		return -EINVAL;

	factor = 0x10000 - factor;
	a = (factor & 0xff00) | divisor;

	/*
	 * CH341A buffers data until a full endpoint-size packet (32 bytes)
	 * has been received unless bit 7 is set.
	 */
	a |= BIT(7);

	r = ch341_control_out(dev, CH341_REQ_WRITE_REG, 0x1312, a);
	if (r)
		return r;

	r = ch341_control_out(dev, CH341_REQ_WRITE_REG, 0x2518, lcr);
	if (r)
		return r;

	return r;
}
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
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int rtl28xxu_rd_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int*) ; 
 int rtl28xxu_wr_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl28xxu_wr_reg_mask(struct dvb_usb_device *d, u16 reg, u8 val,
		u8 mask)
{
	int ret;
	u8 tmp;

	/* no need for read if whole reg is written */
	if (mask != 0xff) {
		ret = rtl28xxu_rd_reg(d, reg, &tmp);
		if (ret)
			return ret;

		val &= mask;
		tmp &= ~mask;
		val |= tmp;
	}

	return rtl28xxu_wr_reg(d, reg, val);
}
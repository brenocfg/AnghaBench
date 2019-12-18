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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int af9035_rd_regs (struct dvb_usb_device*,int /*<<< orphan*/ ,int*,int) ; 
 int af9035_wr_regs (struct dvb_usb_device*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int af9035_wr_reg_mask(struct dvb_usb_device *d, u32 reg, u8 val,
		u8 mask)
{
	int ret;
	u8 tmp;

	/* no need for read if whole reg is written */
	if (mask != 0xff) {
		ret = af9035_rd_regs(d, reg, &tmp, 1);
		if (ret)
			return ret;

		val &= mask;
		tmp &= ~mask;
		val |= tmp;
	}

	return af9035_wr_regs(d, reg, &val, 1);
}
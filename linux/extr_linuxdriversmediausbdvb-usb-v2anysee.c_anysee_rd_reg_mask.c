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
 int anysee_read_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int anysee_rd_reg_mask(struct dvb_usb_device *d, u16 reg, u8 *val,
	u8 mask)
{
	int ret, i;
	u8 tmp;

	ret = anysee_read_reg(d, reg, &tmp);
	if (ret)
		return ret;

	tmp &= mask;

	/* find position of the first bit */
	for (i = 0; i < 8; i++) {
		if ((mask >> i) & 0x01)
			break;
	}
	*val = tmp >> i;

	return 0;
}
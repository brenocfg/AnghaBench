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
 int af9005_read_ofdm_register (struct dvb_usb_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  deb_reg (char*,...) ; 
 int* regmask ; 

int af9005_read_register_bits(struct dvb_usb_device *d, u16 reg, u8 pos,
			      u8 len, u8 * value)
{
	u8 temp;
	int ret;
	deb_reg("read bits %x %x %x", reg, pos, len);
	ret = af9005_read_ofdm_register(d, reg, &temp);
	if (ret) {
		deb_reg(" failed\n");
		return ret;
	}
	*value = (temp >> pos) & regmask[len - 1];
	deb_reg(" value %x\n", *value);
	return 0;

}
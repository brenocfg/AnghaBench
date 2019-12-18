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
typedef  int u32 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int af9005_write_register_bits (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  reg_bw_len ; 
 int /*<<< orphan*/  reg_bw_pos ; 
 int /*<<< orphan*/  xd_g_reg_bw ; 

__attribute__((used)) static int af9005_fe_select_bw(struct dvb_usb_device *d, u32 bw)
{
	u8 temp;
	switch (bw) {
	case 6000000:
		temp = 0;
		break;
	case 7000000:
		temp = 1;
		break;
	case 8000000:
		temp = 2;
		break;
	default:
		err("Invalid bandwidth %d.", bw);
		return -EINVAL;
	}
	return af9005_write_register_bits(d, xd_g_reg_bw, reg_bw_pos,
					  reg_bw_len, temp);
}
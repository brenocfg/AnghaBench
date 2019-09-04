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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct req_t {scalar_t__ member_1; int member_3; int member_4; int member_5; scalar_t__* member_6; int addr_len; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct dvb_usb_device {int dummy; } ;
struct af9015_state {scalar_t__* af9013_i2c_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_I2C ; 
 int af9015_ctrl_msg (struct dvb_usb_device*,struct req_t*) ; 
 struct af9015_state* d_to_priv (struct dvb_usb_device*) ; 

__attribute__((used)) static int af9015_write_reg_i2c(struct dvb_usb_device *d, u8 addr, u16 reg,
				u8 val)
{
	struct af9015_state *state = d_to_priv(d);
	struct req_t req = {WRITE_I2C, addr, reg, 1, 1, 1, &val};

	if (addr == state->af9013_i2c_addr[0] ||
	    addr == state->af9013_i2c_addr[1])
		req.addr_len = 3;

	return af9015_ctrl_msg(d, &req);
}
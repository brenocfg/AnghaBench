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
struct dvb_usb_device {int /*<<< orphan*/  rc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_IR_CODE ; 
 int /*<<< orphan*/  RC_PROTO_NEC ; 
 int /*<<< orphan*/  RC_SCANCODE_NEC (int,int) ; 
 int /*<<< orphan*/  cxusb_ctrl_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxusb_rc_query(struct dvb_usb_device *d)
{
	u8 ircode[4];

	cxusb_ctrl_msg(d, CMD_GET_IR_CODE, NULL, 0, ircode, 4);

	if (ircode[2] || ircode[3])
		rc_keydown(d->rc_dev, RC_PROTO_NEC,
			   RC_SCANCODE_NEC(~ircode[2] & 0xff, ircode[3]), 0);
	return 0;
}
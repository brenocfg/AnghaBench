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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct rtl28xxu_req {int value; int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  index; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_IR_WR ; 
 int /*<<< orphan*/  CMD_SYS_WR ; 
 int /*<<< orphan*/  CMD_USB_WR ; 
 int rtl28xxu_ctrl_msg (struct dvb_usb_device*,struct rtl28xxu_req*) ; 

__attribute__((used)) static int rtl28xxu_wr_regs(struct dvb_usb_device *d, u16 reg, u8 *val, int len)
{
	struct rtl28xxu_req req;

	if (reg < 0x3000)
		req.index = CMD_USB_WR;
	else if (reg < 0x4000)
		req.index = CMD_SYS_WR;
	else
		req.index = CMD_IR_WR;

	req.value = reg;
	req.size = len;
	req.data = val;

	return rtl28xxu_ctrl_msg(d, &req);
}
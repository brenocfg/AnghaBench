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
struct dvb_usb_device {int dummy; } ;
struct dvb_ca_en50221 {struct dvb_usb_device* data; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CMD_CI ; 
 int anysee_ctrl_msg (struct dvb_usb_device*,int*,int,int*,int) ; 

__attribute__((used)) static int anysee_ci_read_attribute_mem(struct dvb_ca_en50221 *ci, int slot,
	int addr)
{
	struct dvb_usb_device *d = ci->data;
	int ret;
	u8 buf[] = {CMD_CI, 0x02, 0x40 | addr >> 8, addr & 0xff, 0x00, 1};
	u8 val;

	ret = anysee_ctrl_msg(d, buf, sizeof(buf), &val, 1);
	if (ret)
		return ret;

	return val;
}
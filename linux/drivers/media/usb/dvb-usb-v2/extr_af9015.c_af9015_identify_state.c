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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct req_t {int member_5; int* member_6; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;

/* Variables and functions */
 int COLD ; 
 int /*<<< orphan*/  GET_CONFIG ; 
 int WARM ; 
 int af9015_ctrl_msg (struct dvb_usb_device*,struct req_t*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int af9015_identify_state(struct dvb_usb_device *d, const char **name)
{
	struct usb_interface *intf = d->intf;
	int ret;
	u8 reply;
	struct req_t req = {GET_CONFIG, 0, 0, 0, 0, 1, &reply};

	ret = af9015_ctrl_msg(d, &req);
	if (ret)
		return ret;

	dev_dbg(&intf->dev, "reply %02x\n", reply);

	if (reply == 0x02)
		ret = WARM;
	else
		ret = COLD;

	return ret;
}
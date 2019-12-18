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
typedef  int u16 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct req_t {int member_2; unsigned int const member_5; int* member_6; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_MEMORY ; 
 int af9015_ctrl_msg (struct dvb_usb_device*,struct req_t*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int af9015_regmap_read(void *context, const void *reg_buf,
			      size_t reg_size, void *val_buf, size_t val_size)
{
	struct dvb_usb_device *d = context;
	struct usb_interface *intf = d->intf;
	int ret;
	u16 reg = ((u8 *)reg_buf)[0] << 8 | ((u8 *)reg_buf)[1] << 0;
	u8 *val = &((u8 *)val_buf)[0];
	const unsigned int len = val_size;
	struct req_t req = {READ_MEMORY, 0, reg, 0, 0, len, val};

	ret = af9015_ctrl_msg(d, &req);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&intf->dev, "failed %d\n", ret);
	return ret;
}
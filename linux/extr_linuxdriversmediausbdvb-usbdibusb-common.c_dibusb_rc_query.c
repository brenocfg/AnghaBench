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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIBUSB_REQ_POLL_REMOTE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  deb_info (char*,int,scalar_t__*) ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,scalar_t__*,int,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_usb_nec_rc_key_to_event (struct dvb_usb_device*,scalar_t__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 

int dibusb_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	u8 *buf;
	int ret;

	buf = kmalloc(5, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf[0] = DIBUSB_REQ_POLL_REMOTE;

	ret = dvb_usb_generic_rw(d, buf, 1, buf, 5, 0);
	if (ret < 0)
		goto ret;

	dvb_usb_nec_rc_key_to_event(d, buf, event, state);

	if (buf[0] != 0)
		deb_info("key: %*ph\n", 5, buf);

ret:
	kfree(buf);

	return ret;
}
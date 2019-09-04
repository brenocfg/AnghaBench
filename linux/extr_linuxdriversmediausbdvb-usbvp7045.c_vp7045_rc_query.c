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
 int /*<<< orphan*/  RC_PROTO_NEC ; 
 int /*<<< orphan*/  RC_SCANCODE_NEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RC_VAL_READ ; 
 int /*<<< orphan*/  deb_rc (char*,int,int) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vp7045_usb_op (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int vp7045_rc_query(struct dvb_usb_device *d)
{
	u8 key;
	vp7045_usb_op(d,RC_VAL_READ,NULL,0,&key,1,20);

	deb_rc("remote query key: %x %d\n",key,key);

	if (key != 0x44) {
		/*
		 * The 8 bit address isn't available, but since the remote uses
		 * address 0 we'll use that. nec repeats are ignored too, even
		 * though the remote sends them.
		 */
		rc_keydown(d->rc_dev, RC_PROTO_NEC, RC_SCANCODE_NEC(0, key), 0);
	}

	return 0;
}
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
struct dvb_usb_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int az6027_usb_out_op (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int az6027_frontend_tsbypass(struct dvb_usb_adapter *adap, int onoff)
{
	int ret;
	u8 req;
	u16 value;
	u16 index;
	int blen;

	/* TS passthrough */
	req = 0xC7;
	value = onoff;
	index = 0;
	blen = 0;

	ret = az6027_usb_out_op(adap->dev, req, value, index, NULL, blen);
	if (ret != 0)
		return -EIO;

	return 0;
}
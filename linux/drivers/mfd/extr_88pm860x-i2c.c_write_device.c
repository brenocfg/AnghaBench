#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_msg {int len; unsigned char* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_adapter {TYPE_1__* algo; } ;
struct TYPE_2__ {int (* master_xfer ) (struct i2c_adapter*,struct i2c_msg*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,void*,int) ; 
 int stub1 (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int write_device(struct i2c_client *i2c, int reg,
			int bytes, void *src)
{
	unsigned char buf[2];
	struct i2c_adapter *adap = i2c->adapter;
	struct i2c_msg msg;
	int ret;

	buf[0] = (unsigned char)reg;
	memcpy(&buf[1], src, bytes);
	msg.addr = i2c->addr;
	msg.flags = 0;
	msg.len = bytes + 1;
	msg.buf = buf;

	ret = adap->algo->master_xfer(adap, &msg, 1);
	if (ret < 0)
		return ret;
	return 0;
}
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
struct solo_dev {int /*<<< orphan*/ * i2c_adap; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

void solo_i2c_writebyte(struct solo_dev *solo_dev, int id, u8 addr,
			u8 off, u8 data)
{
	struct i2c_msg msgs;
	u8 buf[2];

	buf[0] = off;
	buf[1] = data;
	msgs.flags = 0;
	msgs.addr = addr;
	msgs.len = 2;
	msgs.buf = buf;

	i2c_transfer(&solo_dev->i2c_adap[id], &msgs, 1);
}
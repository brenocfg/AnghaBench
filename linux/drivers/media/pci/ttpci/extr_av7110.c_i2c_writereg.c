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
struct i2c_msg {int addr; int len; int* buf; scalar_t__ flags; } ;
struct av7110 {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

int i2c_writereg(struct av7110 *av7110, u8 id, u8 reg, u8 val)
{
	u8 msg[2] = { reg, val };
	struct i2c_msg msgs;

	msgs.flags = 0;
	msgs.addr = id / 2;
	msgs.len = 2;
	msgs.buf = msg;
	return i2c_transfer(&av7110->i2c_adap, &msgs, 1);
}
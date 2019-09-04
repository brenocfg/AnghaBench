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
struct pt1 {int dummy; } ;
struct i2c_msg {int addr; int len; int* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt1_i2c_prepare (struct pt1*,int,int*) ; 
 int /*<<< orphan*/  pt1_i2c_write_byte (struct pt1*,int,int*,int) ; 

__attribute__((used)) static void
pt1_i2c_write_msg(struct pt1 *pt1, int addr, int *addrp, struct i2c_msg *msg)
{
	int i;
	pt1_i2c_prepare(pt1, addr, &addr);
	pt1_i2c_write_byte(pt1, addr, &addr, msg->addr << 1);
	for (i = 0; i < msg->len; i++)
		pt1_i2c_write_byte(pt1, addr, &addr, msg->buf[i]);
	*addrp = addr;
}
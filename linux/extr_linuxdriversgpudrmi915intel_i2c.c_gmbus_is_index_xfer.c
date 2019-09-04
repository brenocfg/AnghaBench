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
struct i2c_msg {scalar_t__ addr; int flags; int len; } ;

/* Variables and functions */
 int I2C_M_RD ; 

__attribute__((used)) static bool
gmbus_is_index_xfer(struct i2c_msg *msgs, int i, int num)
{
	return (i + 1 < num &&
		msgs[i].addr == msgs[i + 1].addr &&
		!(msgs[i].flags & I2C_M_RD) &&
		(msgs[i].len == 1 || msgs[i].len == 2) &&
		msgs[i + 1].len > 0);
}
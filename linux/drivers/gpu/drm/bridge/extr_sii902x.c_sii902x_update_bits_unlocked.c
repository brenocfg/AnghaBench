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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int sii902x_read_unlocked (struct i2c_client*,int,int*) ; 
 int sii902x_write_unlocked (struct i2c_client*,int,int) ; 

__attribute__((used)) static int sii902x_update_bits_unlocked(struct i2c_client *i2c, u8 reg, u8 mask,
					u8 val)
{
	int ret;
	u8 status;

	ret = sii902x_read_unlocked(i2c, reg, &status);
	if (ret)
		return ret;
	status &= ~mask;
	status |= val & mask;
	return sii902x_write_unlocked(i2c, reg, status);
}
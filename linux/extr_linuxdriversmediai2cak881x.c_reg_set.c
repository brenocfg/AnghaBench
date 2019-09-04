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
 int reg_read (struct i2c_client*,int const) ; 
 int reg_write (struct i2c_client*,int const,int) ; 

__attribute__((used)) static int reg_set(struct i2c_client *client, const u8 reg,
		   const u8 data, u8 mask)
{
	int ret = reg_read(client, reg);
	if (ret < 0)
		return ret;
	return reg_write(client, reg, (ret & ~mask) | (data & mask));
}
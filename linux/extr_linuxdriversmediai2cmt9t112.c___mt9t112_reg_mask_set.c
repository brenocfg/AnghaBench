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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int __mt9t112_reg_read (struct i2c_client const*,int) ; 
 int __mt9t112_reg_write (struct i2c_client const*,int,int) ; 

__attribute__((used)) static int __mt9t112_reg_mask_set(const struct i2c_client *client,
				  u16  command, u16  mask, u16  set)
{
	int val = __mt9t112_reg_read(client, command);

	if (val < 0)
		return val;

	val &= ~mask;
	val |= set & mask;

	return __mt9t112_reg_write(client, command, val);
}
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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int __mt9v111_addr_space_select (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int __mt9v111_read (struct i2c_client*,int /*<<< orphan*/ ,int*) ; 
 int __mt9v111_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt9v111_update(struct i2c_client *c, u8 addr_space, u8 reg,
			  u16 mask, u16 val)
{
	u16 current_val;
	int ret;

	/* Select register address space first. */
	ret = __mt9v111_addr_space_select(c, addr_space);
	if (ret)
		return ret;

	/* Read the current register value, then update it. */
	ret = __mt9v111_read(c, reg, &current_val);
	if (ret)
		return ret;

	current_val &= ~mask;
	current_val |= (val & mask);
	ret = __mt9v111_write(c, reg, current_val);
	if (ret)
		return ret;

	return 0;
}
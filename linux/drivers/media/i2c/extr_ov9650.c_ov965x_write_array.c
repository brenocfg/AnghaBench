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
struct ov965x {int dummy; } ;
struct i2c_rv {scalar_t__ addr; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ REG_NULL ; 
 int ov965x_write (struct ov965x*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov965x_write_array(struct ov965x *ov965x,
			      const struct i2c_rv *regs)
{
	int i, ret = 0;

	for (i = 0; ret == 0 && regs[i].addr != REG_NULL; i++)
		ret = ov965x_write(ov965x, regs[i].addr, regs[i].value);

	return ret;
}
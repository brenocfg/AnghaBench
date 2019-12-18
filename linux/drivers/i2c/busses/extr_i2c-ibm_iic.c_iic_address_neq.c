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
struct i2c_msg {scalar_t__ addr; int flags; } ;

/* Variables and functions */
 int I2C_M_TEN ; 

__attribute__((used)) static inline int iic_address_neq(const struct i2c_msg* p1,
				  const struct i2c_msg* p2)
{
	return (p1->addr != p2->addr)
		|| ((p1->flags & I2C_M_TEN) != (p2->flags & I2C_M_TEN));
}
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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int __i2c_bit_add_bus (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_add_adapter ; 

int i2c_bit_add_bus(struct i2c_adapter *adap)
{
	return __i2c_bit_add_bus(adap, i2c_add_adapter);
}
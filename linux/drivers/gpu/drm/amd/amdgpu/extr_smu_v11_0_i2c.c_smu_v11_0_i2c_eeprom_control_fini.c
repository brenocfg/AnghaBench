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
 int /*<<< orphan*/  i2c_del_adapter (struct i2c_adapter*) ; 

void smu_v11_0_i2c_eeprom_control_fini(struct i2c_adapter *control)
{
	i2c_del_adapter(control);
}
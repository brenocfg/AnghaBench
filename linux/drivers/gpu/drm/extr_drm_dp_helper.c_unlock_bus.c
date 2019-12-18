#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_mutex; } ;

/* Variables and functions */
 TYPE_1__* i2c_to_aux (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlock_bus(struct i2c_adapter *i2c, unsigned int flags)
{
	mutex_unlock(&i2c_to_aux(i2c)->hw_mutex);
}
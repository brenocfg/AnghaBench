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
struct intel_gmbus {int force_bit; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 struct intel_gmbus* to_intel_gmbus (struct i2c_adapter*) ; 

bool intel_gmbus_is_forced_bit(struct i2c_adapter *adapter)
{
	struct intel_gmbus *bus = to_intel_gmbus(adapter);

	return bus->force_bit;
}
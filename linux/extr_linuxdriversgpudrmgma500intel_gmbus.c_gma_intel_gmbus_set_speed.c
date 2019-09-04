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
struct intel_gmbus {int reg0; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 struct intel_gmbus* to_intel_gmbus (struct i2c_adapter*) ; 

void gma_intel_gmbus_set_speed(struct i2c_adapter *adapter, int speed)
{
	struct intel_gmbus *bus = to_intel_gmbus(adapter);

	/* speed:
	 * 0x0 = 100 KHz
	 * 0x1 = 50 KHz
	 * 0x2 = 400 KHz
	 * 0x3 = 1000 Khz
	 */
	bus->reg0 = (bus->reg0 & ~(0x3 << 8)) | (speed << 8);
}
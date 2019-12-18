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
struct hfi1_i2c_bus {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hfi1_i2c_bus*) ; 

__attribute__((used)) static void clean_i2c_bus(struct hfi1_i2c_bus *bus)
{
	if (bus) {
		i2c_del_adapter(&bus->adapter);
		kfree(bus);
	}
}
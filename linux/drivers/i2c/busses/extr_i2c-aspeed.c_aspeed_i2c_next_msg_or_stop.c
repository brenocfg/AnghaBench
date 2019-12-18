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
struct aspeed_i2c_bus {scalar_t__ msgs_index; scalar_t__ msgs_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspeed_i2c_do_start (struct aspeed_i2c_bus*) ; 
 int /*<<< orphan*/  aspeed_i2c_do_stop (struct aspeed_i2c_bus*) ; 

__attribute__((used)) static void aspeed_i2c_next_msg_or_stop(struct aspeed_i2c_bus *bus)
{
	if (bus->msgs_index + 1 < bus->msgs_count) {
		bus->msgs_index++;
		aspeed_i2c_do_start(bus);
	} else {
		aspeed_i2c_do_stop(bus);
	}
}
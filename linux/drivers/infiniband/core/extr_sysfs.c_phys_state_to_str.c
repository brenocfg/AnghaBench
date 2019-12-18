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
typedef  enum ib_port_phys_state { ____Placeholder_ib_port_phys_state } ib_port_phys_state ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 

__attribute__((used)) static const char *phys_state_to_str(enum ib_port_phys_state phys_state)
{
	static const char * phys_state_str[] = {
		"<unknown>",
		"Sleep",
		"Polling",
		"Disabled",
		"PortConfigurationTraining",
		"LinkUp",
		"LinkErrorRecovery",
		"Phy Test",
	};

	if (phys_state < ARRAY_SIZE(phys_state_str))
		return phys_state_str[phys_state];
	return "<unknown>";
}
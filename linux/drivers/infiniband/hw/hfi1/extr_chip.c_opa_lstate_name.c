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
typedef  size_t u32 ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 

const char *opa_lstate_name(u32 lstate)
{
	static const char * const port_logical_names[] = {
		"PORT_NOP",
		"PORT_DOWN",
		"PORT_INIT",
		"PORT_ARMED",
		"PORT_ACTIVE",
		"PORT_ACTIVE_DEFER",
	};
	if (lstate < ARRAY_SIZE(port_logical_names))
		return port_logical_names[lstate];
	return "unknown";
}
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
 size_t DPU_POWER_HANDLE_DBUS_ID_MAX ; 
 char const** data_bus_name ; 

const char *dpu_power_handle_get_dbus_name(u32 bus_id)
{
	if (bus_id < DPU_POWER_HANDLE_DBUS_ID_MAX)
		return data_bus_name[bus_id];

	return NULL;
}
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
 size_t ACPI_EVENT_MAX ; 
 char const** acpi_gbl_event_types ; 

const char *acpi_ut_get_event_name(u32 event_id)
{

	if (event_id > ACPI_EVENT_MAX) {
		return ("InvalidEventID");
	}

	return (acpi_gbl_event_types[event_id]);
}
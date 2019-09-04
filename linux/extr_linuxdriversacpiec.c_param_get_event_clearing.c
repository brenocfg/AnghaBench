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
struct kernel_param {int dummy; } ;

/* Variables and functions */
#define  ACPI_EC_EVT_TIMING_EVENT 130 
#define  ACPI_EC_EVT_TIMING_QUERY 129 
#define  ACPI_EC_EVT_TIMING_STATUS 128 
 int ec_event_clearing ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static int param_get_event_clearing(char *buffer,
				    const struct kernel_param *kp)
{
	switch (ec_event_clearing) {
	case ACPI_EC_EVT_TIMING_STATUS:
		return sprintf(buffer, "status");
	case ACPI_EC_EVT_TIMING_QUERY:
		return sprintf(buffer, "query");
	case ACPI_EC_EVT_TIMING_EVENT:
		return sprintf(buffer, "event");
	default:
		return sprintf(buffer, "invalid");
	}
	return 0;
}
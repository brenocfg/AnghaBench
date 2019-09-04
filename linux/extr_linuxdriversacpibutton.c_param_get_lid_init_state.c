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
#define  ACPI_BUTTON_LID_INIT_IGNORE 130 
#define  ACPI_BUTTON_LID_INIT_METHOD 129 
#define  ACPI_BUTTON_LID_INIT_OPEN 128 
 int lid_init_state ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static int param_get_lid_init_state(char *buffer,
				    const struct kernel_param *kp)
{
	switch (lid_init_state) {
	case ACPI_BUTTON_LID_INIT_OPEN:
		return sprintf(buffer, "open");
	case ACPI_BUTTON_LID_INIT_METHOD:
		return sprintf(buffer, "method");
	case ACPI_BUTTON_LID_INIT_IGNORE:
		return sprintf(buffer, "ignore");
	default:
		return sprintf(buffer, "invalid");
	}
	return 0;
}
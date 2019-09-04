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
 int /*<<< orphan*/  ACPI_BUTTON_LID_INIT_IGNORE ; 
 int /*<<< orphan*/  ACPI_BUTTON_LID_INIT_METHOD ; 
 int /*<<< orphan*/  ACPI_BUTTON_LID_INIT_OPEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  lid_init_state ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int param_set_lid_init_state(const char *val,
				    const struct kernel_param *kp)
{
	int result = 0;

	if (!strncmp(val, "open", sizeof("open") - 1)) {
		lid_init_state = ACPI_BUTTON_LID_INIT_OPEN;
		pr_info("Notify initial lid state as open\n");
	} else if (!strncmp(val, "method", sizeof("method") - 1)) {
		lid_init_state = ACPI_BUTTON_LID_INIT_METHOD;
		pr_info("Notify initial lid state with _LID return value\n");
	} else if (!strncmp(val, "ignore", sizeof("ignore") - 1)) {
		lid_init_state = ACPI_BUTTON_LID_INIT_IGNORE;
		pr_info("Do not notify initial lid state\n");
	} else
		result = -EINVAL;
	return result;
}
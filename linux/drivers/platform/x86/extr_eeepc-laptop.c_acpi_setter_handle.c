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
struct eeepc_laptop {int cm_supported; int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ AE_OK ; 
 int ENODEV ; 
 scalar_t__ acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char** cm_setv ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 

__attribute__((used)) static int acpi_setter_handle(struct eeepc_laptop *eeepc, int cm,
			      acpi_handle *handle)
{
	const char *method = cm_setv[cm];
	acpi_status status;

	if (method == NULL)
		return -ENODEV;
	if ((eeepc->cm_supported & (0x1 << cm)) == 0)
		return -ENODEV;

	status = acpi_get_handle(eeepc->handle, (char *)method,
				 handle);
	if (status != AE_OK) {
		pr_warn("Error finding %s\n", method);
		return -ENODEV;
	}
	return 0;
}
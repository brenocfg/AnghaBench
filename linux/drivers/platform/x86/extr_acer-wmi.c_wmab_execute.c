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
typedef  int /*<<< orphan*/  u8 ;
struct wmab_args {int dummy; } ;
struct acpi_buffer {int length; int /*<<< orphan*/ * pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AMW0_GUID1 ; 
 int /*<<< orphan*/  wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct acpi_buffer*,struct acpi_buffer*) ; 

__attribute__((used)) static acpi_status wmab_execute(struct wmab_args *regbuf,
struct acpi_buffer *result)
{
	struct acpi_buffer input;
	acpi_status status;
	input.length = sizeof(struct wmab_args);
	input.pointer = (u8 *)regbuf;

	status = wmi_evaluate_method(AMW0_GUID1, 0, 1, &input, result);

	return status;
}
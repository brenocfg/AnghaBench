#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ thread_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  descriptor_type; } ;
union acpi_generic_state {TYPE_2__ thread; TYPE_1__ common; } ;
struct acpi_thread_state {int dummy; } ;
typedef  scalar_t__ acpi_thread_id ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DESC_TYPE_STATE_THREAD ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ acpi_os_get_thread_id () ; 
 union acpi_generic_state* acpi_ut_create_generic_state () ; 

struct acpi_thread_state *acpi_ut_create_thread_state(void)
{
	union acpi_generic_state *state;

	ACPI_FUNCTION_ENTRY();

	/* Create the generic state object */

	state = acpi_ut_create_generic_state();
	if (!state) {
		return (NULL);
	}

	/* Init fields specific to the update struct */

	state->common.descriptor_type = ACPI_DESC_TYPE_STATE_THREAD;
	state->thread.thread_id = acpi_os_get_thread_id();

	/* Check for invalid thread ID - zero is very bad, it will break things */

	if (!state->thread.thread_id) {
		ACPI_ERROR((AE_INFO, "Invalid zero ID from AcpiOsGetThreadId"));
		state->thread.thread_id = (acpi_thread_id) 1;
	}

	return ((struct acpi_thread_state *)state);
}
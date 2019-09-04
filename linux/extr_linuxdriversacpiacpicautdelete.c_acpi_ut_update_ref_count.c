#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ reference_count; int /*<<< orphan*/  type; } ;
union acpi_operand_object {TYPE_1__ common; } ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  acpi_cpu_flags ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GET_FUNCTION_NAME ; 
 scalar_t__ ACPI_MAX_REFERENCE_COUNT ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
#define  REF_DECREMENT 129 
#define  REF_INCREMENT 128 
 int /*<<< orphan*/  acpi_gbl_reference_count_lock ; 
 int /*<<< orphan*/  acpi_os_acquire_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_release_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_delete_internal_obj (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ut_update_ref_count ; 

__attribute__((used)) static void
acpi_ut_update_ref_count(union acpi_operand_object *object, u32 action)
{
	u16 original_count;
	u16 new_count = 0;
	acpi_cpu_flags lock_flags;
	char *message;

	ACPI_FUNCTION_NAME(ut_update_ref_count);

	if (!object) {
		return;
	}

	/*
	 * Always get the reference count lock. Note: Interpreter and/or
	 * Namespace is not always locked when this function is called.
	 */
	lock_flags = acpi_os_acquire_lock(acpi_gbl_reference_count_lock);
	original_count = object->common.reference_count;

	/* Perform the reference count action (increment, decrement) */

	switch (action) {
	case REF_INCREMENT:

		new_count = original_count + 1;
		object->common.reference_count = new_count;
		acpi_os_release_lock(acpi_gbl_reference_count_lock, lock_flags);

		/* The current reference count should never be zero here */

		if (!original_count) {
			ACPI_WARNING((AE_INFO,
				      "Obj %p, Reference Count was zero before increment\n",
				      object));
		}

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "Obj %p Type %.2X [%s] Refs %.2X [Incremented]\n",
				  object, object->common.type,
				  acpi_ut_get_object_type_name(object),
				  new_count));
		message = "Incremement";
		break;

	case REF_DECREMENT:

		/* The current reference count must be non-zero */

		if (original_count) {
			new_count = original_count - 1;
			object->common.reference_count = new_count;
		}

		acpi_os_release_lock(acpi_gbl_reference_count_lock, lock_flags);

		if (!original_count) {
			ACPI_WARNING((AE_INFO,
				      "Obj %p, Reference Count is already zero, cannot decrement\n",
				      object));
		}

		ACPI_DEBUG_PRINT_RAW((ACPI_DB_ALLOCATIONS,
				      "%s: Obj %p Type %.2X Refs %.2X [Decremented]\n",
				      ACPI_GET_FUNCTION_NAME, object,
				      object->common.type, new_count));

		/* Actually delete the object on a reference count of zero */

		if (new_count == 0) {
			acpi_ut_delete_internal_obj(object);
		}
		message = "Decrement";
		break;

	default:

		acpi_os_release_lock(acpi_gbl_reference_count_lock, lock_flags);
		ACPI_ERROR((AE_INFO, "Unknown Reference Count action (0x%X)",
			    action));
		return;
	}

	/*
	 * Sanity check the reference count, for debug purposes only.
	 * (A deleted object will have a huge reference count)
	 */
	if (new_count > ACPI_MAX_REFERENCE_COUNT) {
		ACPI_WARNING((AE_INFO,
			      "Large Reference Count (0x%X) in object %p, Type=0x%.2X Operation=%s",
			      new_count, object, object->common.type, message));
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ sync_level; int /*<<< orphan*/  acquisition_depth; int /*<<< orphan*/  node; struct acpi_thread_state* owner_thread; } ;
union acpi_operand_object {TYPE_4__ mutex; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {TYPE_3__* thread; } ;
struct acpi_thread_state {scalar_t__ thread_id; scalar_t__ current_sync_level; TYPE_2__* acquired_mutex_list; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_7__ {scalar_t__ thread_id; int /*<<< orphan*/  current_sync_level; } ;
struct TYPE_5__ {scalar_t__ original_sync_level; } ;
struct TYPE_6__ {TYPE_1__ mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_MUTEX_NOT_ACQUIRED ; 
 int /*<<< orphan*/  AE_AML_MUTEX_ORDER ; 
 int /*<<< orphan*/  AE_AML_NOT_OWNER ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ex_release_mutex_object (union acpi_operand_object*) ; 
 union acpi_operand_object* acpi_gbl_global_lock_mutex ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_release_mutex ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_release_mutex(union acpi_operand_object *obj_desc,
		      struct acpi_walk_state *walk_state)
{
	u8 previous_sync_level;
	struct acpi_thread_state *owner_thread;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_release_mutex);

	if (!obj_desc) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	owner_thread = obj_desc->mutex.owner_thread;

	/* The mutex must have been previously acquired in order to release it */

	if (!owner_thread) {
		ACPI_ERROR((AE_INFO,
			    "Cannot release Mutex [%4.4s], not acquired",
			    acpi_ut_get_node_name(obj_desc->mutex.node)));
		return_ACPI_STATUS(AE_AML_MUTEX_NOT_ACQUIRED);
	}

	/* Must have a valid thread ID */

	if (!walk_state->thread) {
		ACPI_ERROR((AE_INFO,
			    "Cannot release Mutex [%4.4s], null thread info",
			    acpi_ut_get_node_name(obj_desc->mutex.node)));
		return_ACPI_STATUS(AE_AML_INTERNAL);
	}

	/*
	 * The Mutex is owned, but this thread must be the owner.
	 * Special case for Global Lock, any thread can release
	 */
	if ((owner_thread->thread_id != walk_state->thread->thread_id) &&
	    (obj_desc != acpi_gbl_global_lock_mutex)) {
		ACPI_ERROR((AE_INFO,
			    "Thread %u cannot release Mutex [%4.4s] acquired by thread %u",
			    (u32)walk_state->thread->thread_id,
			    acpi_ut_get_node_name(obj_desc->mutex.node),
			    (u32)owner_thread->thread_id));
		return_ACPI_STATUS(AE_AML_NOT_OWNER);
	}

	/*
	 * The sync level of the mutex must be equal to the current sync level. In
	 * other words, the current level means that at least one mutex at that
	 * level is currently being held. Attempting to release a mutex of a
	 * different level can only mean that the mutex ordering rule is being
	 * violated. This behavior is clarified in ACPI 4.0 specification.
	 */
	if (obj_desc->mutex.sync_level != owner_thread->current_sync_level) {
		ACPI_ERROR((AE_INFO,
			    "Cannot release Mutex [%4.4s], SyncLevel mismatch: "
			    "mutex %u current %u",
			    acpi_ut_get_node_name(obj_desc->mutex.node),
			    obj_desc->mutex.sync_level,
			    walk_state->thread->current_sync_level));
		return_ACPI_STATUS(AE_AML_MUTEX_ORDER);
	}

	/*
	 * Get the previous sync_level from the head of the acquired mutex list.
	 * This handles the case where several mutexes at the same level have been
	 * acquired, but are not released in reverse order.
	 */
	previous_sync_level =
	    owner_thread->acquired_mutex_list->mutex.original_sync_level;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Releasing: Object SyncLevel %u, Thread SyncLevel %u, "
			  "Prev SyncLevel %u, Depth %u TID %p\n",
			  obj_desc->mutex.sync_level,
			  walk_state->thread->current_sync_level,
			  previous_sync_level,
			  obj_desc->mutex.acquisition_depth,
			  walk_state->thread));

	status = acpi_ex_release_mutex_object(obj_desc);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	if (obj_desc->mutex.acquisition_depth == 0) {

		/* Restore the previous sync_level */

		owner_thread->current_sync_level = previous_sync_level;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Released: Object SyncLevel %u, Thread SyncLevel, %u, "
			  "Prev SyncLevel %u, Depth %u\n",
			  obj_desc->mutex.sync_level,
			  walk_state->thread->current_sync_level,
			  previous_sync_level,
			  obj_desc->mutex.acquisition_depth));

	return_ACPI_STATUS(status);
}
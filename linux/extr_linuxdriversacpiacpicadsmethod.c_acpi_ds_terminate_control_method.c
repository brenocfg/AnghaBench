#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int info_flags; int thread_count; scalar_t__ node; int /*<<< orphan*/  owner_id; scalar_t__ sync_level; TYPE_3__* mutex; } ;
union acpi_operand_object {TYPE_5__ method; } ;
struct acpi_walk_state {TYPE_6__* method_node; TYPE_1__* thread; } ;
struct acpi_namespace_node {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  ascii; } ;
struct TYPE_12__ {TYPE_4__ name; } ;
struct TYPE_8__ {scalar_t__ thread_id; int /*<<< orphan*/  os_mutex; int /*<<< orphan*/  original_sync_level; int /*<<< orphan*/  acquisition_depth; } ;
struct TYPE_9__ {TYPE_2__ mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  current_sync_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 int ACPI_METHOD_IGNORE_SYNC_LEVEL ; 
 int ACPI_METHOD_MODIFIED_NAMESPACE ; 
 int ACPI_METHOD_MODULE_LEVEL ; 
 int ACPI_METHOD_SERIALIZED ; 
 int ACPI_METHOD_SERIALIZED_PENDING ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_ds_method_data_delete_all (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_stop_trace_method (struct acpi_namespace_node*,union acpi_operand_object*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ns_delete_namespace_by_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_delete_namespace_subtree (TYPE_6__*) ; 
 int /*<<< orphan*/  acpi_os_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_owner_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds_terminate_control_method ; 
 int /*<<< orphan*/  return_VOID ; 

void
acpi_ds_terminate_control_method(union acpi_operand_object *method_desc,
				 struct acpi_walk_state *walk_state)
{

	ACPI_FUNCTION_TRACE_PTR(ds_terminate_control_method, walk_state);

	/* method_desc is required, walk_state is optional */

	if (!method_desc) {
		return_VOID;
	}

	if (walk_state) {

		/* Delete all arguments and locals */

		acpi_ds_method_data_delete_all(walk_state);

		/*
		 * Delete any namespace objects created anywhere within the
		 * namespace by the execution of this method. Unless:
		 * 1) This method is a module-level executable code method, in which
		 *    case we want make the objects permanent.
		 * 2) There are other threads executing the method, in which case we
		 *    will wait until the last thread has completed.
		 */
		if (!(method_desc->method.info_flags & ACPI_METHOD_MODULE_LEVEL)
		    && (method_desc->method.thread_count == 1)) {

			/* Delete any direct children of (created by) this method */

			(void)acpi_ex_exit_interpreter();
			acpi_ns_delete_namespace_subtree(walk_state->
							 method_node);
			(void)acpi_ex_enter_interpreter();

			/*
			 * Delete any objects that were created by this method
			 * elsewhere in the namespace (if any were created).
			 * Use of the ACPI_METHOD_MODIFIED_NAMESPACE optimizes the
			 * deletion such that we don't have to perform an entire
			 * namespace walk for every control method execution.
			 */
			if (method_desc->method.
			    info_flags & ACPI_METHOD_MODIFIED_NAMESPACE) {
				(void)acpi_ex_exit_interpreter();
				acpi_ns_delete_namespace_by_owner(method_desc->
								  method.
								  owner_id);
				(void)acpi_ex_enter_interpreter();
				method_desc->method.info_flags &=
				    ~ACPI_METHOD_MODIFIED_NAMESPACE;
			}
		}

		/*
		 * If method is serialized, release the mutex and restore the
		 * current sync level for this thread
		 */
		if (method_desc->method.mutex) {

			/* Acquisition Depth handles recursive calls */

			method_desc->method.mutex->mutex.acquisition_depth--;
			if (!method_desc->method.mutex->mutex.acquisition_depth) {
				walk_state->thread->current_sync_level =
				    method_desc->method.mutex->mutex.
				    original_sync_level;

				acpi_os_release_mutex(method_desc->method.
						      mutex->mutex.os_mutex);
				method_desc->method.mutex->mutex.thread_id = 0;
			}
		}
	}

	/* Decrement the thread count on the method */

	if (method_desc->method.thread_count) {
		method_desc->method.thread_count--;
	} else {
		ACPI_ERROR((AE_INFO, "Invalid zero thread count in method"));
	}

	/* Are there any other threads currently executing this method? */

	if (method_desc->method.thread_count) {
		/*
		 * Additional threads. Do not release the owner_id in this case,
		 * we immediately reuse it for the next thread executing this method
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "*** Completed execution of one thread, %u threads remaining\n",
				  method_desc->method.thread_count));
	} else {
		/* This is the only executing thread for this method */

		/*
		 * Support to dynamically change a method from not_serialized to
		 * Serialized if it appears that the method is incorrectly written and
		 * does not support multiple thread execution. The best example of this
		 * is if such a method creates namespace objects and blocks. A second
		 * thread will fail with an AE_ALREADY_EXISTS exception.
		 *
		 * This code is here because we must wait until the last thread exits
		 * before marking the method as serialized.
		 */
		if (method_desc->method.
		    info_flags & ACPI_METHOD_SERIALIZED_PENDING) {
			if (walk_state) {
				ACPI_INFO(("Marking method %4.4s as Serialized "
					   "because of AE_ALREADY_EXISTS error",
					   walk_state->method_node->name.
					   ascii));
			}

			/*
			 * Method tried to create an object twice and was marked as
			 * "pending serialized". The probable cause is that the method
			 * cannot handle reentrancy.
			 *
			 * The method was created as not_serialized, but it tried to create
			 * a named object and then blocked, causing the second thread
			 * entrance to begin and then fail. Workaround this problem by
			 * marking the method permanently as Serialized when the last
			 * thread exits here.
			 */
			method_desc->method.info_flags &=
			    ~ACPI_METHOD_SERIALIZED_PENDING;

			method_desc->method.info_flags |=
			    (ACPI_METHOD_SERIALIZED |
			     ACPI_METHOD_IGNORE_SYNC_LEVEL);
			method_desc->method.sync_level = 0;
		}

		/* No more threads, we can free the owner_id */

		if (!
		    (method_desc->method.
		     info_flags & ACPI_METHOD_MODULE_LEVEL)) {
			acpi_ut_release_owner_id(&method_desc->method.owner_id);
		}
	}

	acpi_ex_stop_trace_method((struct acpi_namespace_node *)method_desc->
				  method.node, method_desc, walk_state);

	return_VOID;
}
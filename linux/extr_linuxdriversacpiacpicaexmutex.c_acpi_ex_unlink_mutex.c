#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* next; int /*<<< orphan*/  original_sync_level; TYPE_3__* prev; struct acpi_thread_state* owner_thread; } ;
union acpi_operand_object {TYPE_5__ mutex; } ;
struct acpi_thread_state {TYPE_4__* acquired_mutex_list; } ;
struct TYPE_6__ {TYPE_3__* prev; } ;
struct TYPE_9__ {TYPE_1__ mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  original_sync_level; TYPE_4__* next; } ;
struct TYPE_8__ {TYPE_2__ mutex; } ;

/* Variables and functions */

void acpi_ex_unlink_mutex(union acpi_operand_object *obj_desc)
{
	struct acpi_thread_state *thread = obj_desc->mutex.owner_thread;

	if (!thread) {
		return;
	}

	/* Doubly linked list */

	if (obj_desc->mutex.next) {
		(obj_desc->mutex.next)->mutex.prev = obj_desc->mutex.prev;
	}

	if (obj_desc->mutex.prev) {
		(obj_desc->mutex.prev)->mutex.next = obj_desc->mutex.next;

		/*
		 * Migrate the previous sync level associated with this mutex to
		 * the previous mutex on the list so that it may be preserved.
		 * This handles the case where several mutexes have been acquired
		 * at the same level, but are not released in opposite order.
		 */
		(obj_desc->mutex.prev)->mutex.original_sync_level =
		    obj_desc->mutex.original_sync_level;
	} else {
		thread->acquired_mutex_list = obj_desc->mutex.next;
	}
}
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
struct acpi_rw_lock {int /*<<< orphan*/ * writer_mutex; int /*<<< orphan*/ * reader_mutex; scalar_t__ num_readers; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_os_delete_mutex (int /*<<< orphan*/ *) ; 

void acpi_ut_delete_rw_lock(struct acpi_rw_lock *lock)
{

	acpi_os_delete_mutex(lock->reader_mutex);
	acpi_os_delete_mutex(lock->writer_mutex);

	lock->num_readers = 0;
	lock->reader_mutex = NULL;
	lock->writer_mutex = NULL;
}
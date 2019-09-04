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
struct acpi_rw_lock {int /*<<< orphan*/  writer_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_os_release_mutex (int /*<<< orphan*/ ) ; 

void acpi_ut_release_write_lock(struct acpi_rw_lock *lock)
{

	acpi_os_release_mutex(lock->writer_mutex);
}
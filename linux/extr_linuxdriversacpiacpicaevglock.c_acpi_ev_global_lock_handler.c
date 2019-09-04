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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_cpu_flags ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INTERRUPT_HANDLED ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ FALSE ; 
 scalar_t__ acpi_gbl_global_lock_pending ; 
 int /*<<< orphan*/  acpi_gbl_global_lock_pending_lock ; 
 int /*<<< orphan*/  acpi_gbl_global_lock_semaphore ; 
 int /*<<< orphan*/  acpi_os_acquire_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_release_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_signal_semaphore (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 acpi_ev_global_lock_handler(void *context)
{
	acpi_status status;
	acpi_cpu_flags flags;

	flags = acpi_os_acquire_lock(acpi_gbl_global_lock_pending_lock);

	/*
	 * If a request for the global lock is not actually pending,
	 * we are done. This handles "spurious" global lock interrupts
	 * which are possible (and have been seen) with bad BIOSs.
	 */
	if (!acpi_gbl_global_lock_pending) {
		goto cleanup_and_exit;
	}

	/*
	 * Send a unit to the global lock semaphore. The actual acquisition
	 * of the global lock will be performed by the waiting thread.
	 */
	status = acpi_os_signal_semaphore(acpi_gbl_global_lock_semaphore, 1);
	if (ACPI_FAILURE(status)) {
		ACPI_ERROR((AE_INFO, "Could not signal Global Lock semaphore"));
	}

	acpi_gbl_global_lock_pending = FALSE;

cleanup_and_exit:

	acpi_os_release_lock(acpi_gbl_global_lock_pending_lock, flags);
	return (ACPI_INTERRUPT_HANDLED);
}
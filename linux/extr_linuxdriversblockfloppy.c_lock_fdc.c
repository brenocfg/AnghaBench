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

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  FD_COMMAND_NONE ; 
 scalar_t__ WARN (int,char*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_status ; 
 int /*<<< orphan*/  fdc_busy ; 
 int /*<<< orphan*/  fdc_wait ; 
 int /*<<< orphan*/  reschedule_timeout (int,char*) ; 
 int /*<<< orphan*/  set_fdc (int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage_count ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lock_fdc(int drive)
{
	if (WARN(atomic_read(&usage_count) == 0,
		 "Trying to lock fdc while usage count=0\n"))
		return -1;

	if (wait_event_interruptible(fdc_wait, !test_and_set_bit(0, &fdc_busy)))
		return -EINTR;

	command_status = FD_COMMAND_NONE;

	reschedule_timeout(drive, "lock fdc");
	set_fdc(drive);
	return 0;
}
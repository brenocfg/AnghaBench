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
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  FD_COMMAND_NONE ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_status ; 
 int /*<<< orphan*/ * cont ; 
 int /*<<< orphan*/ * do_floppy ; 
 int /*<<< orphan*/  fd_timeout ; 
 int /*<<< orphan*/  fdc_busy ; 
 int /*<<< orphan*/  fdc_wait ; 
 int /*<<< orphan*/ * raw_cmd ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlock_fdc(void)
{
	if (!test_bit(0, &fdc_busy))
		DPRINT("FDC access conflict!\n");

	raw_cmd = NULL;
	command_status = FD_COMMAND_NONE;
	cancel_delayed_work(&fd_timeout);
	do_floppy = NULL;
	cont = NULL;
	clear_bit(0, &fdc_busy);
	wake_up(&fdc_wait);
}
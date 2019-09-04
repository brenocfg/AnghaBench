#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int flags; scalar_t__ cmd_count; scalar_t__ track; } ;

/* Variables and functions */
 TYPE_4__* DP ; 
 TYPE_3__* DRS ; 
 int /*<<< orphan*/  FD_DISK_NEWCHANGE_BIT ; 
 int /*<<< orphan*/ * cont ; 
 int /*<<< orphan*/  debug_dcl (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ default_raw_cmd ; 
 int /*<<< orphan*/  floppy_ready ; 
 int /*<<< orphan*/  poll_cont ; 
 TYPE_1__* raw_cmd ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_til_done (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int poll_drive(bool interruptible, int flag)
{
	/* no auto-sense, just clear dcl */
	raw_cmd = &default_raw_cmd;
	raw_cmd->flags = flag;
	raw_cmd->track = 0;
	raw_cmd->cmd_count = 0;
	cont = &poll_cont;
	debug_dcl(DP->flags, "setting NEWCHANGE in poll_drive\n");
	set_bit(FD_DISK_NEWCHANGE_BIT, &DRS->flags);

	return wait_til_done(floppy_ready, interruptible);
}
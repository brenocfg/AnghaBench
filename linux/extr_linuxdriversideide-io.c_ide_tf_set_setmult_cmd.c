#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ide_taskfile {int /*<<< orphan*/  command; int /*<<< orphan*/  nsect; } ;
struct TYPE_3__ {int /*<<< orphan*/  mult_req; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_SET_MULTI ; 

__attribute__((used)) static void ide_tf_set_setmult_cmd(ide_drive_t *drive, struct ide_taskfile *tf)
{
	tf->nsect   = drive->mult_req;
	tf->command = ATA_CMD_SET_MULTI;
}
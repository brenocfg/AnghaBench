#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* pc; TYPE_2__* hwif; } ;
typedef  TYPE_4__ ide_drive_t ;
struct TYPE_9__ {int /*<<< orphan*/  c; } ;
struct TYPE_8__ {TYPE_1__* tp_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* output_data ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int WAIT_FLOPPY_CMD ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ide_delayed_transfer_pc(ide_drive_t *drive)
{
	/* Send the actual packet */
	drive->hwif->tp_ops->output_data(drive, NULL, drive->pc->c, 12);

	/* Timeout for the packet command */
	return WAIT_FLOPPY_CMD;
}
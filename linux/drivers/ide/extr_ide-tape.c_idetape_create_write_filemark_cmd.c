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
struct ide_atapi_pc {int* c; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_FLAG_WAIT_FOR_DSC ; 
 int WRITE_FILEMARKS ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 

__attribute__((used)) static void idetape_create_write_filemark_cmd(ide_drive_t *drive,
		struct ide_atapi_pc *pc, int write_filemark)
{
	ide_init_pc(pc);
	pc->c[0] = WRITE_FILEMARKS;
	pc->c[4] = write_filemark;
	pc->flags |= PC_FLAG_WAIT_FOR_DSC;
}
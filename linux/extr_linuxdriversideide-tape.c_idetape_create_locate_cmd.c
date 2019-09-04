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
typedef  int u8 ;
struct ide_atapi_pc {int* c; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_FLAG_WAIT_FOR_DSC ; 
 int POSITION_TO_ELEMENT ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void idetape_create_locate_cmd(ide_drive_t *drive,
		struct ide_atapi_pc *pc,
		unsigned int block, u8 partition, int skip)
{
	ide_init_pc(pc);
	pc->c[0] = POSITION_TO_ELEMENT;
	pc->c[1] = 2;
	put_unaligned(cpu_to_be32(block), (unsigned int *) &pc->c[3]);
	pc->c[8] = partition;
	pc->flags |= PC_FLAG_WAIT_FOR_DSC;
}
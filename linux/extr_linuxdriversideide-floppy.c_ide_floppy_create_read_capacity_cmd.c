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
struct ide_atapi_pc {int* c; int req_xfer; } ;

/* Variables and functions */
 int GPCMD_READ_FORMAT_CAPACITIES ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 

void ide_floppy_create_read_capacity_cmd(struct ide_atapi_pc *pc)
{
	ide_init_pc(pc);
	pc->c[0] = GPCMD_READ_FORMAT_CAPACITIES;
	pc->c[7] = 255;
	pc->c[8] = 255;
	pc->req_xfer = 255;
}
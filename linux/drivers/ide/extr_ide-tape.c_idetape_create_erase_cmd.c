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

/* Variables and functions */
 int ERASE ; 
 int /*<<< orphan*/  PC_FLAG_WAIT_FOR_DSC ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 

__attribute__((used)) static void idetape_create_erase_cmd(struct ide_atapi_pc *pc)
{
	ide_init_pc(pc);
	pc->c[0] = ERASE;
	pc->c[1] = 1;
	pc->flags |= PC_FLAG_WAIT_FOR_DSC;
}
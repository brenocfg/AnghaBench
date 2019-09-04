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
struct ide_atapi_pc {int* c; int req_xfer; } ;

/* Variables and functions */
 int IDETAPE_BLOCK_DESCRIPTOR ; 
 int IDETAPE_CAPABILITIES_PAGE ; 
 int MODE_SENSE ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 

__attribute__((used)) static void idetape_create_mode_sense_cmd(struct ide_atapi_pc *pc, u8 page_code)
{
	ide_init_pc(pc);
	pc->c[0] = MODE_SENSE;
	if (page_code != IDETAPE_BLOCK_DESCRIPTOR)
		/* DBD = 1 - Don't return block descriptors */
		pc->c[1] = 8;
	pc->c[2] = page_code;
	/*
	 * Changed pc->c[3] to 0 (255 will at best return unused info).
	 *
	 * For SCSI this byte is defined as subpage instead of high byte
	 * of length and some IDE drives seem to interpret it this way
	 * and return an error when 255 is used.
	 */
	pc->c[3] = 0;
	/* We will just discard data in that case */
	pc->c[4] = 255;
	if (page_code == IDETAPE_BLOCK_DESCRIPTOR)
		pc->req_xfer = 12;
	else if (page_code == IDETAPE_CAPABILITIES_PAGE)
		pc->req_xfer = 24;
	else
		pc->req_xfer = 50;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned short u32 ;
struct nvme_ns {int lba_shift; TYPE_1__* ctrl; } ;
struct gendisk {int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int oncs; int quirks; scalar_t__ max_hw_sectors; } ;

/* Variables and functions */
 int NVME_CTRL_ONCS_WRITE_ZEROES ; 
 int NVME_QUIRK_DISABLE_WRITE_ZEROES ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  blk_queue_max_write_zeroes_sectors (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void nvme_config_write_zeroes(struct gendisk *disk, struct nvme_ns *ns)
{
	u32 max_sectors;
	unsigned short bs = 1 << ns->lba_shift;

	if (!(ns->ctrl->oncs & NVME_CTRL_ONCS_WRITE_ZEROES) ||
	    (ns->ctrl->quirks & NVME_QUIRK_DISABLE_WRITE_ZEROES))
		return;
	/*
	 * Even though NVMe spec explicitly states that MDTS is not
	 * applicable to the write-zeroes:- "The restriction does not apply to
	 * commands that do not transfer data between the host and the
	 * controller (e.g., Write Uncorrectable ro Write Zeroes command).".
	 * In order to be more cautious use controller's max_hw_sectors value
	 * to configure the maximum sectors for the write-zeroes which is
	 * configured based on the controller's MDTS field in the
	 * nvme_init_identify() if available.
	 */
	if (ns->ctrl->max_hw_sectors == UINT_MAX)
		max_sectors = ((u32)(USHRT_MAX + 1) * bs) >> 9;
	else
		max_sectors = ((u32)(ns->ctrl->max_hw_sectors + 1) * bs) >> 9;

	blk_queue_max_write_zeroes_sectors(disk->queue, max_sectors);
}
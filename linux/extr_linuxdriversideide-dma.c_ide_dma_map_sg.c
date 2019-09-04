#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct ide_cmd {int tf_flags; int sg_nents; int orig_sg_nents; int /*<<< orphan*/  sg_dma_direction; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; struct scatterlist* sg_table; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int IDE_TFLAG_WRITE ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ide_dma_map_sg(ide_drive_t *drive, struct ide_cmd *cmd)
{
	ide_hwif_t *hwif = drive->hwif;
	struct scatterlist *sg = hwif->sg_table;
	int i;

	if (cmd->tf_flags & IDE_TFLAG_WRITE)
		cmd->sg_dma_direction = DMA_TO_DEVICE;
	else
		cmd->sg_dma_direction = DMA_FROM_DEVICE;

	i = dma_map_sg(hwif->dev, sg, cmd->sg_nents, cmd->sg_dma_direction);
	if (i) {
		cmd->orig_sg_nents = cmd->sg_nents;
		cmd->sg_nents = i;
	}

	return i;
}
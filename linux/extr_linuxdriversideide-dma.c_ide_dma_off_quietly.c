#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* hwif; int /*<<< orphan*/  dev_flags; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_7__ {TYPE_1__* dma_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* dma_host_set ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_DFLAG_USING_DMA ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void ide_dma_off_quietly(ide_drive_t *drive)
{
	drive->dev_flags &= ~IDE_DFLAG_USING_DMA;

	drive->hwif->dma_ops->dma_host_set(drive, 0);
}
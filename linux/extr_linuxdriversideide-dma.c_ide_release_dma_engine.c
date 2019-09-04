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
struct TYPE_3__ {int prd_max_nents; int prd_ent_size; int /*<<< orphan*/ * dmatable_cpu; int /*<<< orphan*/  dmatable_dma; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ide_release_dma_engine(ide_hwif_t *hwif)
{
	if (hwif->dmatable_cpu) {
		int prd_size = hwif->prd_max_nents * hwif->prd_ent_size;

		dma_free_coherent(hwif->dev, prd_size,
				  hwif->dmatable_cpu, hwif->dmatable_dma);
		hwif->dmatable_cpu = NULL;
	}
}
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
struct TYPE_3__ {scalar_t__ swdma_mask; scalar_t__ mwdma_mask; scalar_t__ ultra_mask; int /*<<< orphan*/  dma_base; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 scalar_t__ no_piix_dma ; 

__attribute__((used)) static void init_hwif_piix(ide_hwif_t *hwif)
{
	if (!hwif->dma_base)
		return;

	if (no_piix_dma)
		hwif->ultra_mask = hwif->mwdma_mask = hwif->swdma_mask = 0;
}
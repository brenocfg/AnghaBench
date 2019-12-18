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
struct mmc_host {unsigned int max_segs; scalar_t__ can_dma_map_merge; } ;

/* Variables and functions */
 unsigned int MMC_DMA_MAP_MERGE_SEGMENTS ; 

__attribute__((used)) static unsigned int mmc_get_max_segments(struct mmc_host *host)
{
	return host->can_dma_map_merge ? MMC_DMA_MAP_MERGE_SEGMENTS :
					 host->max_segs;
}
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
typedef  int u32 ;
struct qmu_gpd {int dummy; } ;
struct mtu3_gpd_ring {struct qmu_gpd* start; scalar_t__ dma; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int MAX_GPD_NUM ; 

__attribute__((used)) static dma_addr_t gpd_virt_to_dma(struct mtu3_gpd_ring *ring,
		struct qmu_gpd *gpd)
{
	dma_addr_t dma_base = ring->dma;
	struct qmu_gpd *gpd_head = ring->start;
	u32 offset;

	offset = gpd - gpd_head;
	if (offset >= MAX_GPD_NUM)
		return 0;

	return dma_base + (offset * sizeof(*gpd));
}
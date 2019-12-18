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
struct tegra_smmu {int pfn_mask; } ;
typedef  int dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static bool smmu_dma_addr_valid(struct tegra_smmu *smmu, dma_addr_t addr)
{
	addr >>= 12;
	return (addr & smmu->pfn_mask) == addr;
}
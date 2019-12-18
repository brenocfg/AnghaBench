#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_smmu {TYPE_2__* mc; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {TYPE_1__* soc; } ;
struct TYPE_3__ {int atom_size; int num_address_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMMU_PTC_FLUSH ; 
 int /*<<< orphan*/  SMMU_PTC_FLUSH_HI ; 
 int SMMU_PTC_FLUSH_HI_MASK ; 
 int SMMU_PTC_FLUSH_TYPE_ADR ; 
 int /*<<< orphan*/  smmu_writel (struct tegra_smmu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void smmu_flush_ptc(struct tegra_smmu *smmu, dma_addr_t dma,
				  unsigned long offset)
{
	u32 value;

	offset &= ~(smmu->mc->soc->atom_size - 1);

	if (smmu->mc->soc->num_address_bits > 32) {
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
		value = (dma >> 32) & SMMU_PTC_FLUSH_HI_MASK;
#else
		value = 0;
#endif
		smmu_writel(smmu, value, SMMU_PTC_FLUSH_HI);
	}

	value = (dma + offset) | SMMU_PTC_FLUSH_TYPE_ADR;
	smmu_writel(smmu, value, SMMU_PTC_FLUSH);
}
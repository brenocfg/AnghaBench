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
struct TYPE_2__ {void* des3; } ;
struct dma_extended_desc {TYPE_1__ basic; } ;
struct dma_desc {void* des3; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 void* cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static void init_dma_chain(void *des, dma_addr_t phy_addr,
				  unsigned int size, unsigned int extend_desc)
{
	/*
	 * In chained mode the des3 points to the next element in the ring.
	 * The latest element has to point to the head.
	 */
	int i;
	dma_addr_t dma_phy = phy_addr;

	if (extend_desc) {
		struct dma_extended_desc *p = (struct dma_extended_desc *)des;
		for (i = 0; i < (size - 1); i++) {
			dma_phy += sizeof(struct dma_extended_desc);
			p->basic.des3 = cpu_to_le32((unsigned int)dma_phy);
			p++;
		}
		p->basic.des3 = cpu_to_le32((unsigned int)phy_addr);

	} else {
		struct dma_desc *p = (struct dma_desc *)des;
		for (i = 0; i < (size - 1); i++) {
			dma_phy += sizeof(struct dma_desc);
			p->des3 = cpu_to_le32((unsigned int)dma_phy);
			p++;
		}
		p->des3 = cpu_to_le32((unsigned int)phy_addr);
	}
}
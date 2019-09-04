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
struct solo_p2m_desc {int ctrl; int dma_addr; int ext_addr; int /*<<< orphan*/  cfg; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_P2M_BURST_256 ; 
 int SOLO_P2M_BURST_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLO_P2M_COPY_SIZE (int) ; 
 int /*<<< orphan*/  SOLO_P2M_EXT_INC (int) ; 
 int SOLO_P2M_PCI_INC (int) ; 
 int SOLO_P2M_REPEAT (int) ; 
 int SOLO_P2M_TRANS_ON ; 
 int SOLO_P2M_WRITE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

void solo_p2m_fill_desc(struct solo_p2m_desc *desc, int wr,
			dma_addr_t dma_addr, u32 ext_addr, u32 size,
			int repeat, u32 ext_size)
{
	WARN_ON_ONCE(dma_addr & 0x03);
	WARN_ON_ONCE(!size);

	desc->cfg = SOLO_P2M_COPY_SIZE(size >> 2);
	desc->ctrl = SOLO_P2M_BURST_SIZE(SOLO_P2M_BURST_256) |
		(wr ? SOLO_P2M_WRITE : 0) | SOLO_P2M_TRANS_ON;

	if (repeat) {
		desc->cfg |= SOLO_P2M_EXT_INC(ext_size >> 2);
		desc->ctrl |=  SOLO_P2M_PCI_INC(size >> 2) |
			 SOLO_P2M_REPEAT(repeat);
	}

	desc->dma_addr = dma_addr;
	desc->ext_addr = ext_addr;
}
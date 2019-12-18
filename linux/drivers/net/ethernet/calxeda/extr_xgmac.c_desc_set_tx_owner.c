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
struct xgmac_dma_desc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int DESC_OWN ; 
 int TXDESC_END_RING ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void desc_set_tx_owner(struct xgmac_dma_desc *p, u32 flags)
{
	u32 tmpflags = le32_to_cpu(p->flags);
	tmpflags &= TXDESC_END_RING;
	tmpflags |= flags | DESC_OWN;
	p->flags = cpu_to_le32(tmpflags);
}
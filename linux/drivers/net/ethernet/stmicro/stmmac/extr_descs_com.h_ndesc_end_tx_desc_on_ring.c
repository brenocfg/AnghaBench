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
struct dma_desc {int /*<<< orphan*/  des1; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDES1_END_RING ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ndesc_end_tx_desc_on_ring(struct dma_desc *p, int end)
{
	if (end)
		p->des1 |= cpu_to_le32(TDES1_END_RING);
	else
		p->des1 &= cpu_to_le32(~TDES1_END_RING);
}
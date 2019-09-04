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
struct aq_ring_s {int /*<<< orphan*/  idx; int /*<<< orphan*/  sw_tail; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_atl_reg_tx_dma_desc_tail_ptr_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_atl_a0_hw_tx_ring_tail_update(struct aq_hw_s *self,
					    struct aq_ring_s *ring)
{
	hw_atl_reg_tx_dma_desc_tail_ptr_set(self, ring->sw_tail, ring->idx);
	return 0;
}
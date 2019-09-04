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
struct aq_ring_s {int /*<<< orphan*/  idx; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rdm_rx_desc_en_set (struct aq_hw_s*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_atl_b0_hw_ring_rx_start(struct aq_hw_s *self,
				      struct aq_ring_s *ring)
{
	hw_atl_rdm_rx_desc_en_set(self, 1, ring->idx);
	return aq_hw_err_from_flags(self);
}
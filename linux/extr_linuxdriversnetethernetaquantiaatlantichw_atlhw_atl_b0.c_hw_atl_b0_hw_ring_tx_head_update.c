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
struct aq_ring_s {unsigned int hw_head; int /*<<< orphan*/  idx; } ;
struct aq_hw_s {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_HW_FLAG_ERR_UNPLUG ; 
 int ENXIO ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 scalar_t__ aq_utils_obj_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int hw_atl_tdm_tx_desc_head_ptr_get (struct aq_hw_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_atl_b0_hw_ring_tx_head_update(struct aq_hw_s *self,
					    struct aq_ring_s *ring)
{
	int err = 0;
	unsigned int hw_head_ = hw_atl_tdm_tx_desc_head_ptr_get(self, ring->idx);

	if (aq_utils_obj_test(&self->flags, AQ_HW_FLAG_ERR_UNPLUG)) {
		err = -ENXIO;
		goto err_exit;
	}
	ring->hw_head = hw_head_;
	err = aq_hw_err_from_flags(self);

err_exit:
	return err;
}
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
struct aq_vec_s {int dummy; } ;
struct aq_nic_s {unsigned int aq_vecs; scalar_t__ power_state; int /*<<< orphan*/  aq_hw; TYPE_2__* aq_hw_ops; TYPE_1__* aq_fw_ops; struct aq_vec_s** aq_vec; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hw_set_power ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ AQ_HW_POWER_STATE_D0 ; 
 int /*<<< orphan*/  aq_vec_deinit (struct aq_vec_s*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 

void aq_nic_deinit(struct aq_nic_s *self)
{
	struct aq_vec_s *aq_vec = NULL;
	unsigned int i = 0U;

	if (!self)
		goto err_exit;

	for (i = 0U, aq_vec = self->aq_vec[0];
		self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i])
		aq_vec_deinit(aq_vec);

	if (self->power_state == AQ_HW_POWER_STATE_D0) {
		(void)self->aq_fw_ops->deinit(self->aq_hw);
	} else {
		(void)self->aq_hw_ops->hw_set_power(self->aq_hw,
						   self->power_state);
	}

err_exit:;
}
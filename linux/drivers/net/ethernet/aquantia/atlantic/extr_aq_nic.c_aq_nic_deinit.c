#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct aq_vec_s {int dummy; } ;
struct aq_nic_s {unsigned int aq_vecs; scalar_t__ power_state; int /*<<< orphan*/  fwreq_mutex; TYPE_3__* ndev; TYPE_4__* aq_hw; TYPE_2__* aq_fw_ops; struct aq_vec_s** aq_vec; } ;
struct TYPE_10__ {TYPE_1__* aq_nic_cfg; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_power ) (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* deinit ) (TYPE_4__*) ;} ;
struct TYPE_7__ {scalar_t__ wol; } ;

/* Variables and functions */
 scalar_t__ AQ_HW_POWER_STATE_D0 ; 
 int /*<<< orphan*/  aq_vec_deinit (struct aq_vec_s*) ; 
 scalar_t__ likely (int /*<<< orphan*/  (*) (TYPE_4__*)) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 

void aq_nic_deinit(struct aq_nic_s *self)
{
	struct aq_vec_s *aq_vec = NULL;
	unsigned int i = 0U;

	if (!self)
		goto err_exit;

	for (i = 0U, aq_vec = self->aq_vec[0];
		self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i])
		aq_vec_deinit(aq_vec);

	if (likely(self->aq_fw_ops->deinit)) {
		mutex_lock(&self->fwreq_mutex);
		self->aq_fw_ops->deinit(self->aq_hw);
		mutex_unlock(&self->fwreq_mutex);
	}

	if (self->power_state != AQ_HW_POWER_STATE_D0 ||
	    self->aq_hw->aq_nic_cfg->wol)
		if (likely(self->aq_fw_ops->set_power)) {
			mutex_lock(&self->fwreq_mutex);
			self->aq_fw_ops->set_power(self->aq_hw,
						   self->power_state,
						   self->ndev->dev_addr);
			mutex_unlock(&self->fwreq_mutex);
		}


err_exit:;
}
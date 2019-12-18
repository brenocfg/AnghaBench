#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ coverage_class; } ;
struct TYPE_5__ {TYPE_1__* hw_ops; } ;
struct ath10k {int /*<<< orphan*/  data_lock; int /*<<< orphan*/  set_coverage_class_work; int /*<<< orphan*/  workqueue; TYPE_3__ fw_coverage; TYPE_2__ hw_params; } ;
struct TYPE_4__ {scalar_t__ set_coverage_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ath10k_wmi_queue_set_coverage_class_work(struct ath10k *ar)
{
	if (ar->hw_params.hw_ops->set_coverage_class) {
		spin_lock_bh(&ar->data_lock);

		/* This call only ensures that the modified coverage class
		 * persists in case the firmware sets the registers back to
		 * their default value. So calling it is only necessary if the
		 * coverage class has a non-zero value.
		 */
		if (ar->fw_coverage.coverage_class)
			queue_work(ar->workqueue, &ar->set_coverage_class_work);

		spin_unlock_bh(&ar->data_lock);
	}
}
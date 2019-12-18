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
struct TYPE_3__ {size_t queue_id; } ;
struct qed_queue_cid {TYPE_1__ rel; int /*<<< orphan*/  qid_usage_idx; } ;
struct qed_hwfn {TYPE_2__* p_l2_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * pp_qid_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qed_eth_queue_qid_usage_del(struct qed_hwfn *p_hwfn,
					struct qed_queue_cid *p_cid)
{
	mutex_lock(&p_hwfn->p_l2_info->lock);

	clear_bit(p_cid->qid_usage_idx,
		  p_hwfn->p_l2_info->pp_qid_usage[p_cid->rel.queue_id]);

	mutex_unlock(&p_hwfn->p_l2_info->lock);
}
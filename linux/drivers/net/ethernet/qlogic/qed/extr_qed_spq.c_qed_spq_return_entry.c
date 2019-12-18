#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qed_spq_entry {int dummy; } ;
struct qed_hwfn {TYPE_1__* p_spq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qed_spq_return_entry (struct qed_hwfn*,struct qed_spq_entry*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void qed_spq_return_entry(struct qed_hwfn *p_hwfn, struct qed_spq_entry *p_ent)
{
	spin_lock_bh(&p_hwfn->p_spq->lock);
	__qed_spq_return_entry(p_hwfn, p_ent);
	spin_unlock_bh(&p_hwfn->p_spq->lock);
}
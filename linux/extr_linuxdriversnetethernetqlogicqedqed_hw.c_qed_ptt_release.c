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
struct qed_ptt {int /*<<< orphan*/  list_entry; } ;
struct qed_hwfn {TYPE_1__* p_ptt_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void qed_ptt_release(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	spin_lock_bh(&p_hwfn->p_ptt_pool->lock);
	list_add(&p_ptt->list_entry, &p_hwfn->p_ptt_pool->free_list);
	spin_unlock_bh(&p_hwfn->p_ptt_pool->lock);
}
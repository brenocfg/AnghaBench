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
struct qed_spq_entry {int /*<<< orphan*/ * queue; } ;
struct qed_hwfn {TYPE_1__* p_spq; } ;
struct TYPE_2__ {int /*<<< orphan*/  unlimited_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qed_spq_entry*) ; 
 int /*<<< orphan*/  qed_spq_return_entry (struct qed_hwfn*,struct qed_spq_entry*) ; 

void qed_sp_destroy_request(struct qed_hwfn *p_hwfn,
			    struct qed_spq_entry *p_ent)
{
	/* qed_spq_get_entry() can either get an entry from the free_pool,
	 * or, if no entries are left, allocate a new entry and add it to
	 * the unlimited_pending list.
	 */
	if (p_ent->queue == &p_hwfn->p_spq->unlimited_pending)
		kfree(p_ent);
	else
		qed_spq_return_entry(p_hwfn, p_ent);
}
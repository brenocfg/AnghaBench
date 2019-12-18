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
struct qed_spq_entry {int /*<<< orphan*/  list; } ;
struct qed_hwfn {TYPE_1__* p_spq; } ;
struct TYPE_2__ {int /*<<< orphan*/  free_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __qed_spq_return_entry(struct qed_hwfn *p_hwfn,
				   struct qed_spq_entry *p_ent)
{
	list_add_tail(&p_ent->list, &p_hwfn->p_spq->free_pool);
}
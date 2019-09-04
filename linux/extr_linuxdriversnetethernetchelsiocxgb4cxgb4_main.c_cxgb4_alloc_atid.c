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
union aopen_entry {void* data; union aopen_entry* next; } ;
struct tid_info {int atid_base; int /*<<< orphan*/  atid_lock; int /*<<< orphan*/  atids_in_use; union aopen_entry* afree; union aopen_entry* atid_tab; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int cxgb4_alloc_atid(struct tid_info *t, void *data)
{
	int atid = -1;

	spin_lock_bh(&t->atid_lock);
	if (t->afree) {
		union aopen_entry *p = t->afree;

		atid = (p - t->atid_tab) + t->atid_base;
		t->afree = p->next;
		p->data = data;
		t->atids_in_use++;
	}
	spin_unlock_bh(&t->atid_lock);
	return atid;
}
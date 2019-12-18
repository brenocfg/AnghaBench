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
struct TYPE_3__ {void* ctx; } ;
union active_open_entry {union active_open_entry* next; TYPE_1__ t3c_tid; } ;
struct tid_info {int /*<<< orphan*/  atid_lock; int /*<<< orphan*/  atids_in_use; union active_open_entry* afree; } ;
struct t3cdev {int dummy; } ;
struct TYPE_4__ {struct tid_info tid_maps; } ;

/* Variables and functions */
 TYPE_2__* T3C_DATA (struct t3cdev*) ; 
 union active_open_entry* atid2entry (struct tid_info*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void *cxgb3_free_atid(struct t3cdev *tdev, int atid)
{
	struct tid_info *t = &(T3C_DATA(tdev))->tid_maps;
	union active_open_entry *p = atid2entry(t, atid);
	void *ctx = p->t3c_tid.ctx;

	spin_lock_bh(&t->atid_lock);
	p->next = t->afree;
	t->afree = p;
	t->atids_in_use--;
	spin_unlock_bh(&t->atid_lock);

	return ctx;
}
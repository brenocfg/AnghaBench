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
struct t3cdev {int dummy; } ;
struct t3c_tid_entry {void* ctx; int /*<<< orphan*/ * client; } ;
struct TYPE_2__ {struct t3c_tid_entry* tid_tab; } ;
struct t3c_data {int /*<<< orphan*/  tid_release_lock; int /*<<< orphan*/  tid_release_task; scalar_t__ release_list_incomplete; struct t3c_tid_entry* tid_release_list; TYPE_1__ tid_maps; } ;

/* Variables and functions */
 struct t3c_data* T3C_DATA (struct t3cdev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void cxgb3_queue_tid_release(struct t3cdev *tdev, unsigned int tid)
{
	struct t3c_data *td = T3C_DATA(tdev);
	struct t3c_tid_entry *p = &td->tid_maps.tid_tab[tid];

	spin_lock_bh(&td->tid_release_lock);
	p->ctx = (void *)td->tid_release_list;
	p->client = NULL;
	td->tid_release_list = p;
	if (!p->ctx || td->release_list_incomplete)
		schedule_work(&td->tid_release_task);
	spin_unlock_bh(&td->tid_release_lock);
}
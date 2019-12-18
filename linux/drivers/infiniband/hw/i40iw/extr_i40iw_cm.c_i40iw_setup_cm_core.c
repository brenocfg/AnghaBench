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
struct i40iw_cm_core {void* disconn_wq; void* event_wq; int /*<<< orphan*/  apbvt_lock; int /*<<< orphan*/  listen_list_lock; int /*<<< orphan*/  ht_lock; int /*<<< orphan*/  tcp_timer; int /*<<< orphan*/  listen_nodes; int /*<<< orphan*/  non_accelerated_list; int /*<<< orphan*/  accelerated_list; int /*<<< orphan*/ * dev; struct i40iw_device* iwdev; } ;
struct i40iw_device {struct i40iw_cm_core cm_core; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 void* alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_cleanup_cm_core (struct i40iw_cm_core*) ; 
 int /*<<< orphan*/  i40iw_cm_timer_tick ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int i40iw_setup_cm_core(struct i40iw_device *iwdev)
{
	struct i40iw_cm_core *cm_core = &iwdev->cm_core;

	cm_core->iwdev = iwdev;
	cm_core->dev = &iwdev->sc_dev;

	INIT_LIST_HEAD(&cm_core->accelerated_list);
	INIT_LIST_HEAD(&cm_core->non_accelerated_list);
	INIT_LIST_HEAD(&cm_core->listen_nodes);

	timer_setup(&cm_core->tcp_timer, i40iw_cm_timer_tick, 0);

	spin_lock_init(&cm_core->ht_lock);
	spin_lock_init(&cm_core->listen_list_lock);
	spin_lock_init(&cm_core->apbvt_lock);

	cm_core->event_wq = alloc_ordered_workqueue("iwewq",
						    WQ_MEM_RECLAIM);
	if (!cm_core->event_wq)
		goto error;

	cm_core->disconn_wq = alloc_ordered_workqueue("iwdwq",
						      WQ_MEM_RECLAIM);
	if (!cm_core->disconn_wq)
		goto error;

	return 0;
error:
	i40iw_cleanup_cm_core(&iwdev->cm_core);

	return -ENOMEM;
}
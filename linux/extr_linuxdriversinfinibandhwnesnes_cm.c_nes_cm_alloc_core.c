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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct nes_cm_core {void* event_wq; void* disconn_wq; int /*<<< orphan*/  post_event; TYPE_1__ listen_list; int /*<<< orphan*/  listen_list_lock; int /*<<< orphan*/  ht_lock; int /*<<< orphan*/ * api; int /*<<< orphan*/  events_posted; int /*<<< orphan*/  free_tx_pkt_max; int /*<<< orphan*/  state; int /*<<< orphan*/  mtu; int /*<<< orphan*/  tcp_timer; int /*<<< orphan*/  connected_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NES_CM_DEFAULT_FREE_PKTS ; 
 int /*<<< orphan*/  NES_CM_DEFAULT_MTU ; 
 int /*<<< orphan*/  NES_CM_STATE_INITED ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 void* alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (void*) ; 
 int /*<<< orphan*/  kfree (struct nes_cm_core*) ; 
 struct nes_cm_core* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_cm_api ; 
 int /*<<< orphan*/  nes_cm_post_event ; 
 int /*<<< orphan*/  nes_cm_timer_tick ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_core (struct nes_cm_core*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nes_cm_core *nes_cm_alloc_core(void)
{
	struct nes_cm_core *cm_core;

	/* setup the CM core */
	/* alloc top level core control structure */
	cm_core = kzalloc(sizeof(*cm_core), GFP_KERNEL);
	if (!cm_core)
		return NULL;

	INIT_LIST_HEAD(&cm_core->connected_nodes);
	timer_setup(&cm_core->tcp_timer, nes_cm_timer_tick, 0);

	cm_core->mtu = NES_CM_DEFAULT_MTU;
	cm_core->state = NES_CM_STATE_INITED;
	cm_core->free_tx_pkt_max = NES_CM_DEFAULT_FREE_PKTS;

	atomic_set(&cm_core->events_posted, 0);

	cm_core->api = &nes_cm_api;

	spin_lock_init(&cm_core->ht_lock);
	spin_lock_init(&cm_core->listen_list_lock);

	INIT_LIST_HEAD(&cm_core->listen_list.list);

	nes_debug(NES_DBG_CM, "Init CM Core completed -- cm_core=%p\n", cm_core);

	nes_debug(NES_DBG_CM, "Enable QUEUE EVENTS\n");
	cm_core->event_wq = alloc_ordered_workqueue("nesewq", 0);
	if (!cm_core->event_wq)
		goto out_free_cmcore;
	cm_core->post_event = nes_cm_post_event;
	nes_debug(NES_DBG_CM, "Enable QUEUE DISCONNECTS\n");
	cm_core->disconn_wq = alloc_ordered_workqueue("nesdwq", 0);
	if (!cm_core->disconn_wq)
		goto out_free_wq;

	print_core(cm_core);
	return cm_core;

out_free_wq:
	destroy_workqueue(cm_core->event_wq);
out_free_cmcore:
	kfree(cm_core);
	return NULL;
}
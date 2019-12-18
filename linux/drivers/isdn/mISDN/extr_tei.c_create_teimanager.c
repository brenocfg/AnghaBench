#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  st; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  send; } ;
struct TYPE_7__ {int debug; int /*<<< orphan*/  state; int /*<<< orphan*/ * fsm; int /*<<< orphan*/  printdebug; struct manager* userdata; } ;
struct manager {int nextid; TYPE_2__ ch; int /*<<< orphan*/  datimer; TYPE_3__ deact; TYPE_2__ bcast; int /*<<< orphan*/  lastid; int /*<<< orphan*/  sendq; int /*<<< orphan*/  lock; int /*<<< orphan*/  layer2; } ;
struct TYPE_5__ {int /*<<< orphan*/  st; } ;
struct mISDNdevice {TYPE_2__* teimgr; TYPE_1__ D; } ;

/* Variables and functions */
 int DEBUG_MANAGER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GROUP_TEI ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MISDN_ID_NONE ; 
 int /*<<< orphan*/  ST_L1_DEACT ; 
 int /*<<< orphan*/  TEI_SAPI ; 
 int /*<<< orphan*/  add_layer2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_debug ; 
 int /*<<< orphan*/  deactfsm ; 
 int* debug ; 
 struct manager* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmInitTimer (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgr_bcast ; 
 int /*<<< orphan*/  mgr_bcast_ctrl ; 
 int /*<<< orphan*/  mgr_ctrl ; 
 int /*<<< orphan*/  mgr_send ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_channel_address (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

int
create_teimanager(struct mISDNdevice *dev)
{
	struct manager *mgr;

	mgr = kzalloc(sizeof(struct manager), GFP_KERNEL);
	if (!mgr)
		return -ENOMEM;
	INIT_LIST_HEAD(&mgr->layer2);
	rwlock_init(&mgr->lock);
	skb_queue_head_init(&mgr->sendq);
	mgr->nextid = 1;
	mgr->lastid = MISDN_ID_NONE;
	mgr->ch.send = mgr_send;
	mgr->ch.ctrl = mgr_ctrl;
	mgr->ch.st = dev->D.st;
	set_channel_address(&mgr->ch, TEI_SAPI, GROUP_TEI);
	add_layer2(&mgr->ch, dev->D.st);
	mgr->bcast.send = mgr_bcast;
	mgr->bcast.ctrl = mgr_bcast_ctrl;
	mgr->bcast.st = dev->D.st;
	set_channel_address(&mgr->bcast, 0, GROUP_TEI);
	add_layer2(&mgr->bcast, dev->D.st);
	mgr->deact.debug = *debug & DEBUG_MANAGER;
	mgr->deact.userdata = mgr;
	mgr->deact.printdebug = da_debug;
	mgr->deact.fsm = &deactfsm;
	mgr->deact.state = ST_L1_DEACT;
	mISDN_FsmInitTimer(&mgr->deact, &mgr->datimer);
	dev->teimgr = &mgr->ch;
	return 0;
}
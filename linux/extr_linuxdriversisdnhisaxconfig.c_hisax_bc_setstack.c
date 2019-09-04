#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hisax_d_if {TYPE_3__** b_if; } ;
struct TYPE_10__ {int /*<<< orphan*/  l2l1; } ;
struct TYPE_9__ {size_t bc; struct BCState* bcs; struct IsdnCardState* hardware; } ;
struct PStack {TYPE_5__ l2; TYPE_4__ l1; } ;
struct TYPE_6__ {struct hisax_d_if* hisax_d_if; } ;
struct IsdnCardState {TYPE_1__ hw; } ;
struct TYPE_7__ {TYPE_3__* b_if; } ;
struct BCState {size_t channel; int /*<<< orphan*/  squeue; int /*<<< orphan*/  rqueue; struct PStack* st; TYPE_2__ hw; } ;
struct TYPE_8__ {struct BCState* bcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisax_b_l2l1 ; 
 int /*<<< orphan*/  setstack_l1_B (struct PStack*) ; 
 int /*<<< orphan*/  setstack_manager (struct PStack*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisax_bc_setstack(struct PStack *st, struct BCState *bcs)
{
	struct IsdnCardState *cs = st->l1.hardware;
	struct hisax_d_if *hisax_d_if = cs->hw.hisax_d_if;

	bcs->channel = st->l1.bc;

	bcs->hw.b_if = hisax_d_if->b_if[st->l1.bc];
	hisax_d_if->b_if[st->l1.bc]->bcs = bcs;

	st->l1.bcs = bcs;
	st->l2.l2l1 = hisax_b_l2l1;
	setstack_manager(st);
	bcs->st = st;
	setstack_l1_B(st);
	skb_queue_head_init(&bcs->rqueue);
	skb_queue_head_init(&bcs->squeue);
	return 0;
}
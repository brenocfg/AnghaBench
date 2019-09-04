#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sk_buff {int* data; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int bchannel; } ;
struct l3_process {TYPE_3__* st; int /*<<< orphan*/  timer; TYPE_1__ para; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_3__*,int,struct l3_process*) ;} ;
struct TYPE_6__ {TYPE_2__ l3; } ;

/* Variables and functions */
 int CC_MORE_INFO ; 
 int /*<<< orphan*/  CC_T304 ; 
 int INDICATION ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T304 ; 
 int /*<<< orphan*/  WE0_chanID ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int* findie (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l3_1tr6_error (struct l3_process*,char*,struct sk_buff*) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3_1tr6_setup_ack(struct l3_process *pc, u_char pr, void *arg)
{
	u_char *p;
	struct sk_buff *skb = arg;

	L3DelTimer(&pc->timer);
	p = skb->data;
	newl3state(pc, 2);
	if ((p = findie(p, skb->len, WE0_chanID, 0))) {
		if (p[1] != 1) {
			l3_1tr6_error(pc, "setup_ack wrong chanID len", skb);
			return;
		}
		if ((p[2] & 0xf4) != 0x80) {
			l3_1tr6_error(pc, "setup_ack wrong WE0_chanID", skb);
			return;
		}
		pc->para.bchannel = p[2] & 0x3;
	} else {
		l3_1tr6_error(pc, "missing setup_ack WE0_chanID", skb);
		return;
	}
	dev_kfree_skb(skb);
	L3AddTimer(&pc->timer, T304, CC_T304);
	pc->st->l3.l3l4(pc->st, CC_MORE_INFO | INDICATION, pc);
}
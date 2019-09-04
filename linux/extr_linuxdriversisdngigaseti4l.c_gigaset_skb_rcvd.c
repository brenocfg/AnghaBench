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
struct sk_buff {int dummy; } ;
struct bc_state {int /*<<< orphan*/  trans_down; int /*<<< orphan*/  channel; TYPE_1__* cs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* rcvcallb_skb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ;} ;
typedef  TYPE_2__ isdn_if ;
struct TYPE_3__ {int /*<<< orphan*/  myid; TYPE_2__* iif; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 

void gigaset_skb_rcvd(struct bc_state *bcs, struct sk_buff *skb)
{
	isdn_if *iif = bcs->cs->iif;

	iif->rcvcallb_skb(bcs->cs->myid, bcs->channel, skb);
	bcs->trans_down++;
}
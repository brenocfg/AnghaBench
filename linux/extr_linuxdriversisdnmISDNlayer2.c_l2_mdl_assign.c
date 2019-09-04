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
struct sk_buff {int dummy; } ;
struct layer2 {int dummy; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDL_ASSIGN_IND ; 
 int /*<<< orphan*/  ST_L2_3 ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2_tei (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
l2_mdl_assign(struct FsmInst *fi, int event, void *arg)
{
	struct layer2	*l2 = fi->userdata;

	mISDN_FsmChangeState(fi, ST_L2_3);
	dev_kfree_skb((struct sk_buff *)arg);
	l2_tei(l2, MDL_ASSIGN_IND, 0);
}
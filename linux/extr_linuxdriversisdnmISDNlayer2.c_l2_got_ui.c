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
struct layer2 {scalar_t__ tm; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_UNITDATA_IND ; 
 int /*<<< orphan*/  MDL_STATUS_UI_IND ; 
 int /*<<< orphan*/  l2_tei (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2headersize (struct layer2*,int) ; 
 int /*<<< orphan*/  l2up (struct layer2*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
l2_got_ui(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;
	struct sk_buff *skb = arg;

	skb_pull(skb, l2headersize(l2, 1));
/*
 *		in states 1-3 for broadcast
 */

	if (l2->tm)
		l2_tei(l2, MDL_STATUS_UI_IND, 0);
	l2up(l2, DL_UNITDATA_IND, skb);
}
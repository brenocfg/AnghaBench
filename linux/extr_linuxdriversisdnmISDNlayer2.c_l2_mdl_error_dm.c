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
struct layer2 {int /*<<< orphan*/  flag; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L3_INIT ; 
 int /*<<< orphan*/  MDL_ERROR_IND ; 
 int /*<<< orphan*/  establishlink (struct FsmInst*) ; 
 scalar_t__ get_PollFlagFree (struct layer2*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2mgr (struct layer2*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_mdl_error_dm(struct FsmInst *fi, int event, void *arg)
{
	struct sk_buff *skb = arg;
	struct layer2 *l2 = fi->userdata;

	if (get_PollFlagFree(l2, skb))
		l2mgr(l2, MDL_ERROR_IND, (void *) 'B');
	else {
		l2mgr(l2, MDL_ERROR_IND, (void *) 'E');
		establishlink(fi);
		test_and_clear_bit(FLG_L3_INIT, &l2->flag);
	}
}
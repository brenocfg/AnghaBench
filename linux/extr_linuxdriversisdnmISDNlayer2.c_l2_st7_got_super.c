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
struct sk_buff {int* data; } ;
struct layer2 {unsigned int vs; unsigned int va; int /*<<< orphan*/  i_queue; int /*<<< orphan*/  t203; int /*<<< orphan*/  T203; int /*<<< orphan*/  l2m; int /*<<< orphan*/  flag; } ;
struct FsmInst {struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_L2_ACK_PULL ; 
 int /*<<< orphan*/  EV_L2_T203 ; 
 int /*<<< orphan*/  FLG_MOD128 ; 
 int /*<<< orphan*/  FLG_ORIG ; 
 scalar_t__ IsREJ (int*,struct layer2*) ; 
 scalar_t__ IsRNR (int*,struct layer2*) ; 
 int /*<<< orphan*/  MDL_ERROR_IND ; 
 int REJ ; 
 int RNR ; 
 int RR ; 
 int /*<<< orphan*/  clear_peer_busy (struct layer2*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  enquiry_response (struct layer2*) ; 
 int /*<<< orphan*/  invoke_retransmission (struct layer2*,unsigned int) ; 
 int /*<<< orphan*/  l2addrsize (struct layer2*) ; 
 int /*<<< orphan*/  l2m_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  l2mgr (struct layer2*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ legalnr (struct layer2*,unsigned int) ; 
 scalar_t__ mISDN_FsmAddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mISDN_FsmEvent (struct FsmInst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_FsmRestartTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nrerrorrecovery (struct FsmInst*) ; 
 int /*<<< orphan*/  restart_t200 (struct layer2*,int) ; 
 int /*<<< orphan*/  set_peer_busy (struct layer2*) ; 
 int /*<<< orphan*/  setva (struct layer2*,unsigned int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_t200 (struct layer2*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_st7_got_super(struct FsmInst *fi, int event, void *arg)
{
	struct layer2 *l2 = fi->userdata;
	struct sk_buff *skb = arg;
	int PollFlag, rsp, typ = RR;
	unsigned int nr;

	rsp = *skb->data & 0x2;
	if (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;

	skb_pull(skb, l2addrsize(l2));
	if (IsRNR(skb->data, l2)) {
		set_peer_busy(l2);
		typ = RNR;
	} else
		clear_peer_busy(l2);
	if (IsREJ(skb->data, l2))
		typ = REJ;

	if (test_bit(FLG_MOD128, &l2->flag)) {
		PollFlag = (skb->data[1] & 0x1) == 0x1;
		nr = skb->data[1] >> 1;
	} else {
		PollFlag = (skb->data[0] & 0x10);
		nr = (skb->data[0] >> 5) & 0x7;
	}
	dev_kfree_skb(skb);

	if (PollFlag) {
		if (rsp)
			l2mgr(l2, MDL_ERROR_IND, (void *) 'A');
		else
			enquiry_response(l2);
	}
	if (legalnr(l2, nr)) {
		if (typ == REJ) {
			setva(l2, nr);
			invoke_retransmission(l2, nr);
			stop_t200(l2, 10);
			if (mISDN_FsmAddTimer(&l2->t203, l2->T203,
					      EV_L2_T203, NULL, 6))
				l2m_debug(&l2->l2m, "Restart T203 ST7 REJ");
		} else if ((nr == l2->vs) && (typ == RR)) {
			setva(l2, nr);
			stop_t200(l2, 11);
			mISDN_FsmRestartTimer(&l2->t203, l2->T203,
					      EV_L2_T203, NULL, 7);
		} else if ((l2->va != nr) || (typ == RNR)) {
			setva(l2, nr);
			if (typ != RR)
				mISDN_FsmDelTimer(&l2->t203, 9);
			restart_t200(l2, 12);
		}
		if (skb_queue_len(&l2->i_queue) && (typ == RR))
			mISDN_FsmEvent(fi, EV_L2_ACK_PULL, NULL);
	} else
		nrerrorrecovery(fi);
}
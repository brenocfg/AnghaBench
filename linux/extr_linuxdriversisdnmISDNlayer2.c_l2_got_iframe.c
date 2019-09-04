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
typedef  int u_int ;
struct sk_buff {int* data; } ;
struct layer2 {int vr; int vs; int va; int /*<<< orphan*/  flag; int /*<<< orphan*/  i_queue; int /*<<< orphan*/  T203; int /*<<< orphan*/  t203; } ;
struct FsmInst {scalar_t__ state; struct layer2* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DATA_IND ; 
 int /*<<< orphan*/  EV_L2_ACK_PULL ; 
 int /*<<< orphan*/  EV_L2_T203 ; 
 int /*<<< orphan*/  FLG_ACK_PEND ; 
 int /*<<< orphan*/  FLG_MOD128 ; 
 int /*<<< orphan*/  FLG_OWN_BUSY ; 
 int /*<<< orphan*/  FLG_PEER_BUSY ; 
 int /*<<< orphan*/  FLG_REJEXC ; 
 int /*<<< orphan*/  REJ ; 
 int /*<<< orphan*/  RR ; 
 int /*<<< orphan*/  RSP ; 
 scalar_t__ ST_L2_7 ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  enquiry_cr (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enquiry_response (struct layer2*) ; 
 int l2addrsize (struct layer2*) ; 
 int /*<<< orphan*/  l2headersize (struct layer2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2up (struct layer2*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ legalnr (struct layer2*,int) ; 
 int /*<<< orphan*/  mISDN_FsmEvent (struct FsmInst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_FsmRestartTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nrerrorrecovery (struct FsmInst*) ; 
 int /*<<< orphan*/  restart_t200 (struct layer2*,int) ; 
 int /*<<< orphan*/  setva (struct layer2*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_t200 (struct layer2*,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2_got_iframe(struct FsmInst *fi, int event, void *arg)
{
	struct layer2	*l2 = fi->userdata;
	struct sk_buff	*skb = arg;
	int		PollFlag, i;
	u_int		ns, nr;

	i = l2addrsize(l2);
	if (test_bit(FLG_MOD128, &l2->flag)) {
		PollFlag = ((skb->data[i + 1] & 0x1) == 0x1);
		ns = skb->data[i] >> 1;
		nr = (skb->data[i + 1] >> 1) & 0x7f;
	} else {
		PollFlag = (skb->data[i] & 0x10);
		ns = (skb->data[i] >> 1) & 0x7;
		nr = (skb->data[i] >> 5) & 0x7;
	}
	if (test_bit(FLG_OWN_BUSY, &l2->flag)) {
		dev_kfree_skb(skb);
		if (PollFlag)
			enquiry_response(l2);
	} else {
		if (l2->vr == ns) {
			l2->vr++;
			if (test_bit(FLG_MOD128, &l2->flag))
				l2->vr %= 128;
			else
				l2->vr %= 8;
			test_and_clear_bit(FLG_REJEXC, &l2->flag);
			if (PollFlag)
				enquiry_response(l2);
			else
				test_and_set_bit(FLG_ACK_PEND, &l2->flag);
			skb_pull(skb, l2headersize(l2, 0));
			l2up(l2, DL_DATA_IND, skb);
		} else {
			/* n(s)!=v(r) */
			dev_kfree_skb(skb);
			if (test_and_set_bit(FLG_REJEXC, &l2->flag)) {
				if (PollFlag)
					enquiry_response(l2);
			} else {
				enquiry_cr(l2, REJ, RSP, PollFlag);
				test_and_clear_bit(FLG_ACK_PEND, &l2->flag);
			}
		}
	}
	if (legalnr(l2, nr)) {
		if (!test_bit(FLG_PEER_BUSY, &l2->flag) &&
		    (fi->state == ST_L2_7)) {
			if (nr == l2->vs) {
				stop_t200(l2, 13);
				mISDN_FsmRestartTimer(&l2->t203, l2->T203,
						      EV_L2_T203, NULL, 7);
			} else if (nr != l2->va)
				restart_t200(l2, 14);
		}
		setva(l2, nr);
	} else {
		nrerrorrecovery(fi);
		return;
	}
	if (skb_queue_len(&l2->i_queue) && (fi->state == ST_L2_7))
		mISDN_FsmEvent(fi, EV_L2_ACK_PULL, NULL);
	if (test_and_clear_bit(FLG_ACK_PEND, &l2->flag))
		enquiry_cr(l2, RR, RSP, 0);
}
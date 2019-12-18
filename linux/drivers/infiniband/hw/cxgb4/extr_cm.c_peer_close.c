#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct cpl_peer_close {int dummy; } ;
struct c4iw_qp_attributes {int /*<<< orphan*/  next_state; } ;
struct TYPE_4__ {int state; int /*<<< orphan*/  mutex; TYPE_2__* qp; int /*<<< orphan*/  cm_id; int /*<<< orphan*/  wr_waitp; int /*<<< orphan*/  history; } ;
struct c4iw_ep {TYPE_1__ com; int /*<<< orphan*/  hwtid; int /*<<< orphan*/  dst; } ;
struct c4iw_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  rhp; } ;

/* Variables and functions */
#define  ABORTING 136 
 int /*<<< orphan*/  C4IW_QP_ATTR_NEXT_STATE ; 
 int /*<<< orphan*/  C4IW_QP_STATE_CLOSING ; 
 int /*<<< orphan*/  C4IW_QP_STATE_IDLE ; 
#define  CLOSING 135 
#define  DEAD 134 
 int ECONNRESET ; 
#define  FPDU_MODE 133 
 unsigned int GET_TID (struct cpl_peer_close*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  MORIBUND 132 
#define  MPA_REP_SENT 131 
#define  MPA_REQ_RCVD 130 
#define  MPA_REQ_SENT 129 
#define  MPA_REQ_WAIT 128 
 int /*<<< orphan*/  PEER_CLOSE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  __state_set (TYPE_1__*,int) ; 
 int /*<<< orphan*/  c4iw_ep_disconnect (struct c4iw_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int c4iw_modify_qp (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,struct c4iw_qp_attributes*,int) ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_1__*) ; 
 int /*<<< orphan*/  c4iw_wake_up_noref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close_complete_upcall (struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connect_reply_upcall (struct c4iw_ep*,int) ; 
 struct cpl_peer_close* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dst_confirm (int /*<<< orphan*/ ) ; 
 struct c4iw_ep* get_ep_from_tid (struct c4iw_dev*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peer_close_upcall (struct c4iw_ep*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_ep_resources (struct c4iw_ep*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_ep_timer (struct c4iw_ep*) ; 
 int /*<<< orphan*/  stop_ep_timer (struct c4iw_ep*) ; 

__attribute__((used)) static int peer_close(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct cpl_peer_close *hdr = cplhdr(skb);
	struct c4iw_ep *ep;
	struct c4iw_qp_attributes attrs;
	int disconnect = 1;
	int release = 0;
	unsigned int tid = GET_TID(hdr);
	int ret;

	ep = get_ep_from_tid(dev, tid);
	if (!ep)
		return 0;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	dst_confirm(ep->dst);

	set_bit(PEER_CLOSE, &ep->com.history);
	mutex_lock(&ep->com.mutex);
	switch (ep->com.state) {
	case MPA_REQ_WAIT:
		__state_set(&ep->com, CLOSING);
		break;
	case MPA_REQ_SENT:
		__state_set(&ep->com, CLOSING);
		connect_reply_upcall(ep, -ECONNRESET);
		break;
	case MPA_REQ_RCVD:

		/*
		 * We're gonna mark this puppy DEAD, but keep
		 * the reference on it until the ULP accepts or
		 * rejects the CR. Also wake up anyone waiting
		 * in rdma connection migration (see c4iw_accept_cr()).
		 */
		__state_set(&ep->com, CLOSING);
		pr_debug("waking up ep %p tid %u\n", ep, ep->hwtid);
		c4iw_wake_up_noref(ep->com.wr_waitp, -ECONNRESET);
		break;
	case MPA_REP_SENT:
		__state_set(&ep->com, CLOSING);
		pr_debug("waking up ep %p tid %u\n", ep, ep->hwtid);
		c4iw_wake_up_noref(ep->com.wr_waitp, -ECONNRESET);
		break;
	case FPDU_MODE:
		start_ep_timer(ep);
		__state_set(&ep->com, CLOSING);
		attrs.next_state = C4IW_QP_STATE_CLOSING;
		ret = c4iw_modify_qp(ep->com.qp->rhp, ep->com.qp,
				       C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
		if (ret != -ECONNRESET) {
			peer_close_upcall(ep);
			disconnect = 1;
		}
		break;
	case ABORTING:
		disconnect = 0;
		break;
	case CLOSING:
		__state_set(&ep->com, MORIBUND);
		disconnect = 0;
		break;
	case MORIBUND:
		(void)stop_ep_timer(ep);
		if (ep->com.cm_id && ep->com.qp) {
			attrs.next_state = C4IW_QP_STATE_IDLE;
			c4iw_modify_qp(ep->com.qp->rhp, ep->com.qp,
				       C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
		}
		close_complete_upcall(ep, 0);
		__state_set(&ep->com, DEAD);
		release = 1;
		disconnect = 0;
		break;
	case DEAD:
		disconnect = 0;
		break;
	default:
		WARN_ONCE(1, "Bad endpoint state %u\n", ep->com.state);
	}
	mutex_unlock(&ep->com.mutex);
	if (disconnect)
		c4iw_ep_disconnect(ep, 0, GFP_KERNEL);
	if (release)
		release_ep_resources(ep);
	c4iw_put_ep(&ep->com);
	return 0;
}
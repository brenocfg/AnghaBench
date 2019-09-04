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
struct cpl_close_con_rpl {int dummy; } ;
struct c4iw_qp_attributes {int /*<<< orphan*/  next_state; } ;
struct TYPE_4__ {int state; int /*<<< orphan*/  mutex; TYPE_2__* qp; int /*<<< orphan*/  cm_id; int /*<<< orphan*/  history; } ;
struct c4iw_ep {TYPE_1__ com; int /*<<< orphan*/  hwtid; } ;
struct c4iw_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  rhp; } ;

/* Variables and functions */
#define  ABORTING 131 
 int /*<<< orphan*/  C4IW_QP_ATTR_NEXT_STATE ; 
 int /*<<< orphan*/  C4IW_QP_STATE_IDLE ; 
 int /*<<< orphan*/  CLOSE_CON_RPL ; 
#define  CLOSING 130 
#define  DEAD 129 
 unsigned int GET_TID (struct cpl_close_con_rpl*) ; 
#define  MORIBUND 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  __state_set (TYPE_1__*,int) ; 
 int /*<<< orphan*/  c4iw_modify_qp (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,struct c4iw_qp_attributes*,int) ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_1__*) ; 
 int /*<<< orphan*/  close_complete_upcall (struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 struct cpl_close_con_rpl* cplhdr (struct sk_buff*) ; 
 struct c4iw_ep* get_ep_from_tid (struct c4iw_dev*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_ep_resources (struct c4iw_ep*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_ep_timer (struct c4iw_ep*) ; 

__attribute__((used)) static int close_con_rpl(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct c4iw_ep *ep;
	struct c4iw_qp_attributes attrs;
	struct cpl_close_con_rpl *rpl = cplhdr(skb);
	int release = 0;
	unsigned int tid = GET_TID(rpl);

	ep = get_ep_from_tid(dev, tid);
	if (!ep)
		return 0;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);

	/* The cm_id may be null if we failed to connect */
	mutex_lock(&ep->com.mutex);
	set_bit(CLOSE_CON_RPL, &ep->com.history);
	switch (ep->com.state) {
	case CLOSING:
		__state_set(&ep->com, MORIBUND);
		break;
	case MORIBUND:
		(void)stop_ep_timer(ep);
		if ((ep->com.cm_id) && (ep->com.qp)) {
			attrs.next_state = C4IW_QP_STATE_IDLE;
			c4iw_modify_qp(ep->com.qp->rhp,
					     ep->com.qp,
					     C4IW_QP_ATTR_NEXT_STATE,
					     &attrs, 1);
		}
		close_complete_upcall(ep, 0);
		__state_set(&ep->com, DEAD);
		release = 1;
		break;
	case ABORTING:
	case DEAD:
		break;
	default:
		WARN_ONCE(1, "Bad endpoint state %u\n", ep->com.state);
		break;
	}
	mutex_unlock(&ep->com.mutex);
	if (release)
		release_ep_resources(ep);
	c4iw_put_ep(&ep->com);
	return 0;
}
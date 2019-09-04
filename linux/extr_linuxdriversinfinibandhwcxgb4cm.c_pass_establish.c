#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct cpl_pass_establish {int /*<<< orphan*/  rcv_isn; int /*<<< orphan*/  snd_isn; int /*<<< orphan*/  tcp_opt; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  history; int /*<<< orphan*/  state; } ;
struct c4iw_ep {TYPE_1__ com; int /*<<< orphan*/  dst; int /*<<< orphan*/  snd_wscale; void* rcv_seq; void* snd_seq; int /*<<< orphan*/  hwtid; } ;
struct c4iw_dev {int dummy; } ;

/* Variables and functions */
 unsigned int GET_TID (struct cpl_pass_establish*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MPA_REQ_WAIT ; 
 int /*<<< orphan*/  PASS_ESTAB ; 
 int /*<<< orphan*/  TCPOPT_SND_WSCALE_G (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_ep_disconnect (struct c4iw_ep*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_1__*) ; 
 struct cpl_pass_establish* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dst_confirm (int /*<<< orphan*/ ) ; 
 struct c4iw_ep* get_ep_from_tid (struct c4iw_dev*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,unsigned int,...) ; 
 int send_flowc (struct c4iw_ep*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_emss (struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_ep_timer (struct c4iw_ep*) ; 

__attribute__((used)) static int pass_establish(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct c4iw_ep *ep;
	struct cpl_pass_establish *req = cplhdr(skb);
	unsigned int tid = GET_TID(req);
	int ret;
	u16 tcp_opt = ntohs(req->tcp_opt);

	ep = get_ep_from_tid(dev, tid);
	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	ep->snd_seq = be32_to_cpu(req->snd_isn);
	ep->rcv_seq = be32_to_cpu(req->rcv_isn);
	ep->snd_wscale = TCPOPT_SND_WSCALE_G(tcp_opt);

	pr_debug("ep %p hwtid %u tcp_opt 0x%02x\n", ep, tid, tcp_opt);

	set_emss(ep, tcp_opt);

	dst_confirm(ep->dst);
	mutex_lock(&ep->com.mutex);
	ep->com.state = MPA_REQ_WAIT;
	start_ep_timer(ep);
	set_bit(PASS_ESTAB, &ep->com.history);
	ret = send_flowc(ep);
	mutex_unlock(&ep->com.mutex);
	if (ret)
		c4iw_ep_disconnect(ep, 1, GFP_KERNEL);
	c4iw_put_ep(&ep->com);

	return 0;
}
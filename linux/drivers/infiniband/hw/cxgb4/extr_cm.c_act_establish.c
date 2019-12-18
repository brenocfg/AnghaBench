#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tid_info {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cpl_act_establish {int /*<<< orphan*/  rcv_isn; int /*<<< orphan*/  snd_isn; int /*<<< orphan*/  tos_atid; int /*<<< orphan*/  tcp_opt; } ;
struct TYPE_8__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  history; TYPE_4__* dev; TYPE_3__ local_addr; } ;
struct c4iw_ep {unsigned int hwtid; TYPE_5__ com; scalar_t__ retry_with_mpa_v1; int /*<<< orphan*/  snd_wscale; void* rcv_seq; void* snd_seq; int /*<<< orphan*/  dst; } ;
struct TYPE_6__ {struct tid_info* tids; } ;
struct TYPE_7__ {TYPE_1__ lldi; } ;
struct c4iw_dev {TYPE_2__ rdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  atids; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT_ESTAB ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int GET_TID (struct cpl_act_establish*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TCPOPT_SND_WSCALE_G (unsigned short) ; 
 unsigned int TID_TID_G (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c4iw_ep_disconnect (struct c4iw_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connect_reply_upcall (struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 struct cpl_act_establish* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb4_free_atid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  cxgb4_insert_tid (struct tid_info*,struct c4iw_ep*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_confirm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_ep_tid (struct c4iw_ep*) ; 
 struct c4iw_ep* lookup_atid (struct tid_info*,unsigned int) ; 
 int mpa_rev ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_ep*,unsigned int,void*,void*) ; 
 int send_flowc (struct c4iw_ep*) ; 
 int send_mpa_req (struct c4iw_ep*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_emss (struct c4iw_ep*,unsigned short) ; 
 int /*<<< orphan*/  xa_erase_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int act_establish(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct c4iw_ep *ep;
	struct cpl_act_establish *req = cplhdr(skb);
	unsigned short tcp_opt = ntohs(req->tcp_opt);
	unsigned int tid = GET_TID(req);
	unsigned int atid = TID_TID_G(ntohl(req->tos_atid));
	struct tid_info *t = dev->rdev.lldi.tids;
	int ret;

	ep = lookup_atid(t, atid);

	pr_debug("ep %p tid %u snd_isn %u rcv_isn %u\n", ep, tid,
		 be32_to_cpu(req->snd_isn), be32_to_cpu(req->rcv_isn));

	mutex_lock(&ep->com.mutex);
	dst_confirm(ep->dst);

	/* setup the hwtid for this connection */
	ep->hwtid = tid;
	cxgb4_insert_tid(t, ep, tid, ep->com.local_addr.ss_family);
	insert_ep_tid(ep);

	ep->snd_seq = be32_to_cpu(req->snd_isn);
	ep->rcv_seq = be32_to_cpu(req->rcv_isn);
	ep->snd_wscale = TCPOPT_SND_WSCALE_G(tcp_opt);

	set_emss(ep, tcp_opt);

	/* dealloc the atid */
	xa_erase_irq(&ep->com.dev->atids, atid);
	cxgb4_free_atid(t, atid);
	set_bit(ACT_ESTAB, &ep->com.history);

	/* start MPA negotiation */
	ret = send_flowc(ep);
	if (ret)
		goto err;
	if (ep->retry_with_mpa_v1)
		ret = send_mpa_req(ep, skb, 1);
	else
		ret = send_mpa_req(ep, skb, mpa_rev);
	if (ret)
		goto err;
	mutex_unlock(&ep->com.mutex);
	return 0;
err:
	mutex_unlock(&ep->com.mutex);
	connect_reply_upcall(ep, -ENOMEM);
	c4iw_ep_disconnect(ep, 0, GFP_KERNEL);
	return 0;
}
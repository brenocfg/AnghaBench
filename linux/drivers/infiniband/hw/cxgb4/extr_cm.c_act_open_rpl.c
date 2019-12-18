#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tid_info {int dummy; } ;
struct TYPE_24__ {int /*<<< orphan*/ * s6_addr; } ;
struct sockaddr_in6 {TYPE_8__ sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_21__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_5__ sin_addr; } ;
struct sk_buff {int dummy; } ;
struct cpl_act_open_rpl {int /*<<< orphan*/  atid_status; } ;
struct TYPE_23__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_22__ {scalar_t__ ss_family; } ;
struct TYPE_16__ {TYPE_11__* dev; TYPE_7__ local_addr; TYPE_6__ remote_addr; int /*<<< orphan*/  history; } ;
struct TYPE_17__ {int /*<<< orphan*/  connect_neg_adv; } ;
struct c4iw_ep {TYPE_12__ com; int /*<<< orphan*/  l2t; int /*<<< orphan*/  dst; int /*<<< orphan*/  retry_count; TYPE_1__ stats; } ;
struct TYPE_19__ {int /*<<< orphan*/  enable_fw_ofld_conn; struct tid_info* tids; } ;
struct TYPE_18__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  tcam_full; int /*<<< orphan*/  neg_adv; } ;
struct TYPE_20__ {TYPE_3__ lldi; TYPE_2__ stats; } ;
struct c4iw_dev {TYPE_4__ rdev; } ;
struct TYPE_25__ {int /*<<< orphan*/  tids; int /*<<< orphan*/ * ports; } ;
struct TYPE_14__ {TYPE_9__ lldi; } ;
struct TYPE_15__ {int /*<<< orphan*/  atids; TYPE_10__ rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT_OPEN_RETRY_COUNT ; 
 int /*<<< orphan*/  ACT_OPEN_RPL ; 
 int /*<<< orphan*/  ACT_RETRY_INUSE ; 
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  AOPEN_ATID_G (int /*<<< orphan*/ ) ; 
 int AOPEN_STATUS_G (int /*<<< orphan*/ ) ; 
#define  CPL_ERR_CONN_EXIST 131 
#define  CPL_ERR_CONN_RESET 130 
#define  CPL_ERR_CONN_TIMEDOUT 129 
#define  CPL_ERR_TCAM_FULL 128 
 int /*<<< orphan*/  DEAD ; 
 int /*<<< orphan*/  GET_TID (struct cpl_act_open_rpl*) ; 
 unsigned int TID_TID_G (int /*<<< orphan*/ ) ; 
 scalar_t__ act_open_has_tid (int) ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_12__*) ; 
 int /*<<< orphan*/  c4iw_reconnect (struct c4iw_ep*) ; 
 int /*<<< orphan*/  connect_reply_upcall (struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 struct cpl_act_open_rpl* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb4_clip_release (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  cxgb4_free_atid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  cxgb4_l2t_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_remove_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cxgb_is_neg_adv (int) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ ) ; 
 struct c4iw_ep* lookup_atid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neg_adv_str (int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int send_fw_act_open_req (struct c4iw_ep*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_set (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status2errno (int) ; 
 int /*<<< orphan*/  xa_erase_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int act_open_rpl(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct c4iw_ep *ep;
	struct cpl_act_open_rpl *rpl = cplhdr(skb);
	unsigned int atid = TID_TID_G(AOPEN_ATID_G(
				      ntohl(rpl->atid_status)));
	struct tid_info *t = dev->rdev.lldi.tids;
	int status = AOPEN_STATUS_G(ntohl(rpl->atid_status));
	struct sockaddr_in *la;
	struct sockaddr_in *ra;
	struct sockaddr_in6 *la6;
	struct sockaddr_in6 *ra6;
	int ret = 0;

	ep = lookup_atid(t, atid);
	la = (struct sockaddr_in *)&ep->com.local_addr;
	ra = (struct sockaddr_in *)&ep->com.remote_addr;
	la6 = (struct sockaddr_in6 *)&ep->com.local_addr;
	ra6 = (struct sockaddr_in6 *)&ep->com.remote_addr;

	pr_debug("ep %p atid %u status %u errno %d\n", ep, atid,
		 status, status2errno(status));

	if (cxgb_is_neg_adv(status)) {
		pr_debug("Connection problems for atid %u status %u (%s)\n",
			 atid, status, neg_adv_str(status));
		ep->stats.connect_neg_adv++;
		mutex_lock(&dev->rdev.stats.lock);
		dev->rdev.stats.neg_adv++;
		mutex_unlock(&dev->rdev.stats.lock);
		return 0;
	}

	set_bit(ACT_OPEN_RPL, &ep->com.history);

	/*
	 * Log interesting failures.
	 */
	switch (status) {
	case CPL_ERR_CONN_RESET:
	case CPL_ERR_CONN_TIMEDOUT:
		break;
	case CPL_ERR_TCAM_FULL:
		mutex_lock(&dev->rdev.stats.lock);
		dev->rdev.stats.tcam_full++;
		mutex_unlock(&dev->rdev.stats.lock);
		if (ep->com.local_addr.ss_family == AF_INET &&
		    dev->rdev.lldi.enable_fw_ofld_conn) {
			ret = send_fw_act_open_req(ep, TID_TID_G(AOPEN_ATID_G(
						   ntohl(rpl->atid_status))));
			if (ret)
				goto fail;
			return 0;
		}
		break;
	case CPL_ERR_CONN_EXIST:
		if (ep->retry_count++ < ACT_OPEN_RETRY_COUNT) {
			set_bit(ACT_RETRY_INUSE, &ep->com.history);
			if (ep->com.remote_addr.ss_family == AF_INET6) {
				struct sockaddr_in6 *sin6 =
						(struct sockaddr_in6 *)
						&ep->com.local_addr;
				cxgb4_clip_release(
						ep->com.dev->rdev.lldi.ports[0],
						(const u32 *)
						&sin6->sin6_addr.s6_addr, 1);
			}
			xa_erase_irq(&ep->com.dev->atids, atid);
			cxgb4_free_atid(t, atid);
			dst_release(ep->dst);
			cxgb4_l2t_release(ep->l2t);
			c4iw_reconnect(ep);
			return 0;
		}
		break;
	default:
		if (ep->com.local_addr.ss_family == AF_INET) {
			pr_info("Active open failure - atid %u status %u errno %d %pI4:%u->%pI4:%u\n",
				atid, status, status2errno(status),
				&la->sin_addr.s_addr, ntohs(la->sin_port),
				&ra->sin_addr.s_addr, ntohs(ra->sin_port));
		} else {
			pr_info("Active open failure - atid %u status %u errno %d %pI6:%u->%pI6:%u\n",
				atid, status, status2errno(status),
				la6->sin6_addr.s6_addr, ntohs(la6->sin6_port),
				ra6->sin6_addr.s6_addr, ntohs(ra6->sin6_port));
		}
		break;
	}

fail:
	connect_reply_upcall(ep, status2errno(status));
	state_set(&ep->com, DEAD);

	if (ep->com.remote_addr.ss_family == AF_INET6) {
		struct sockaddr_in6 *sin6 =
			(struct sockaddr_in6 *)&ep->com.local_addr;
		cxgb4_clip_release(ep->com.dev->rdev.lldi.ports[0],
				   (const u32 *)&sin6->sin6_addr.s6_addr, 1);
	}
	if (status && act_open_has_tid(status))
		cxgb4_remove_tid(ep->com.dev->rdev.lldi.tids, 0, GET_TID(rpl),
				 ep->com.local_addr.ss_family);

	xa_erase_irq(&ep->com.dev->atids, atid);
	cxgb4_free_atid(t, atid);
	dst_release(ep->dst);
	cxgb4_l2t_release(ep->l2t);
	c4iw_put_ep(&ep->com);

	return 0;
}
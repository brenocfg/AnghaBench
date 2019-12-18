#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_14__ {unsigned long qid; int flags; } ;
struct TYPE_11__ {int qid; } ;
struct TYPE_13__ {TYPE_7__ sq; TYPE_4__ rq; } ;
struct TYPE_12__ {scalar_t__ state; } ;
struct c4iw_qp {TYPE_6__ wq; TYPE_5__ attr; TYPE_2__* srq; struct c4iw_ep* ep; } ;
struct TYPE_8__ {scalar_t__ ss_family; } ;
struct TYPE_10__ {scalar_t__ state; TYPE_1__ local_addr; } ;
struct c4iw_ep {int hwtid; TYPE_3__ com; } ;
struct c4iw_debugfs_data {int bufsize; int pos; int buf; } ;
struct TYPE_9__ {int idx; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int T4_SQ_ONCHIP ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ep_sin6_addrs (struct c4iw_ep*,struct sockaddr_in6**,struct sockaddr_in6**,struct sockaddr_in6**,struct sockaddr_in6**) ; 
 int /*<<< orphan*/  set_ep_sin_addrs (struct c4iw_ep*,struct sockaddr_in**,struct sockaddr_in**,struct sockaddr_in**,struct sockaddr_in**) ; 
 int snprintf (int,int,char*,int,...) ; 

__attribute__((used)) static int dump_qp(unsigned long id, struct c4iw_qp *qp,
		   struct c4iw_debugfs_data *qpd)
{
	int space;
	int cc;
	if (id != qp->wq.sq.qid)
		return 0;

	space = qpd->bufsize - qpd->pos - 1;
	if (space == 0)
		return 1;

	if (qp->ep) {
		struct c4iw_ep *ep = qp->ep;

		if (ep->com.local_addr.ss_family == AF_INET) {
			struct sockaddr_in *lsin;
			struct sockaddr_in *rsin;
			struct sockaddr_in *m_lsin;
			struct sockaddr_in *m_rsin;

			set_ep_sin_addrs(ep, &lsin, &rsin, &m_lsin, &m_rsin);
			cc = snprintf(qpd->buf + qpd->pos, space,
				      "rc qp sq id %u %s id %u state %u "
				      "onchip %u ep tid %u state %u "
				      "%pI4:%u/%u->%pI4:%u/%u\n",
				      qp->wq.sq.qid, qp->srq ? "srq" : "rq",
				      qp->srq ? qp->srq->idx : qp->wq.rq.qid,
				      (int)qp->attr.state,
				      qp->wq.sq.flags & T4_SQ_ONCHIP,
				      ep->hwtid, (int)ep->com.state,
				      &lsin->sin_addr, ntohs(lsin->sin_port),
				      ntohs(m_lsin->sin_port),
				      &rsin->sin_addr, ntohs(rsin->sin_port),
				      ntohs(m_rsin->sin_port));
		} else {
			struct sockaddr_in6 *lsin6;
			struct sockaddr_in6 *rsin6;
			struct sockaddr_in6 *m_lsin6;
			struct sockaddr_in6 *m_rsin6;

			set_ep_sin6_addrs(ep, &lsin6, &rsin6, &m_lsin6,
					  &m_rsin6);
			cc = snprintf(qpd->buf + qpd->pos, space,
				      "rc qp sq id %u rq id %u state %u "
				      "onchip %u ep tid %u state %u "
				      "%pI6:%u/%u->%pI6:%u/%u\n",
				      qp->wq.sq.qid, qp->wq.rq.qid,
				      (int)qp->attr.state,
				      qp->wq.sq.flags & T4_SQ_ONCHIP,
				      ep->hwtid, (int)ep->com.state,
				      &lsin6->sin6_addr,
				      ntohs(lsin6->sin6_port),
				      ntohs(m_lsin6->sin6_port),
				      &rsin6->sin6_addr,
				      ntohs(rsin6->sin6_port),
				      ntohs(m_rsin6->sin6_port));
		}
	} else
		cc = snprintf(qpd->buf + qpd->pos, space,
			     "qp sq id %u rq id %u state %u onchip %u\n",
			      qp->wq.sq.qid, qp->wq.rq.qid,
			      (int)qp->attr.state,
			      qp->wq.sq.flags & T4_SQ_ONCHIP);
	if (cc < space)
		qpd->pos += cc;
	return 0;
}
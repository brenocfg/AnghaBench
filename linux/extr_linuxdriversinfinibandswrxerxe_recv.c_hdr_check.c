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
typedef  int u32 ;
struct rxe_qp {int dummy; } ;
struct rxe_port {int qp_gsi_index; } ;
struct rxe_pkt_info {int mask; struct rxe_qp* qp; struct rxe_dev* rxe; } ;
struct rxe_dev {int /*<<< orphan*/  qp_pool; struct rxe_port port; } ;

/* Variables and functions */
 scalar_t__ BTH_TVER ; 
 int EINVAL ; 
 int IB_MULTICAST_QPN ; 
 int RXE_GRH_MASK ; 
 int bth_qpn (struct rxe_pkt_info*) ; 
 scalar_t__ bth_tver (struct rxe_pkt_info*) ; 
 int check_addr (struct rxe_dev*,struct rxe_pkt_info*,struct rxe_qp*) ; 
 int check_keys (struct rxe_dev*,struct rxe_pkt_info*,int,struct rxe_qp*) ; 
 int check_type_state (struct rxe_dev*,struct rxe_pkt_info*,struct rxe_qp*) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,...) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_qp*) ; 
 struct rxe_qp* rxe_pool_get_index (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hdr_check(struct rxe_pkt_info *pkt)
{
	struct rxe_dev *rxe = pkt->rxe;
	struct rxe_port *port = &rxe->port;
	struct rxe_qp *qp = NULL;
	u32 qpn = bth_qpn(pkt);
	int index;
	int err;

	if (unlikely(bth_tver(pkt) != BTH_TVER)) {
		pr_warn_ratelimited("bad tver\n");
		goto err1;
	}

	if (unlikely(qpn == 0)) {
		pr_warn_once("QP 0 not supported");
		goto err1;
	}

	if (qpn != IB_MULTICAST_QPN) {
		index = (qpn == 1) ? port->qp_gsi_index : qpn;

		qp = rxe_pool_get_index(&rxe->qp_pool, index);
		if (unlikely(!qp)) {
			pr_warn_ratelimited("no qp matches qpn 0x%x\n", qpn);
			goto err1;
		}

		err = check_type_state(rxe, pkt, qp);
		if (unlikely(err))
			goto err2;

		err = check_addr(rxe, pkt, qp);
		if (unlikely(err))
			goto err2;

		err = check_keys(rxe, pkt, qpn, qp);
		if (unlikely(err))
			goto err2;
	} else {
		if (unlikely((pkt->mask & RXE_GRH_MASK) == 0)) {
			pr_warn_ratelimited("no grh for mcast qpn\n");
			goto err1;
		}
	}

	pkt->qp = qp;
	return 0;

err2:
	rxe_drop_ref(qp);
err1:
	return -EINVAL;
}
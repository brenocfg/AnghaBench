#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {size_t pkey_index; int qkey; } ;
struct rxe_qp {TYPE_2__ attr; } ;
struct TYPE_3__ {int pkey_tbl_len; } ;
struct rxe_port {int /*<<< orphan*/ * pkey_tbl; TYPE_1__ attr; } ;
struct rxe_pkt_info {int pkey_index; scalar_t__ mask; } ;
struct rxe_dev {struct rxe_port port; } ;

/* Variables and functions */
 int EINVAL ; 
 int GSI_QKEY ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  bth_pkey (struct rxe_pkt_info*) ; 
 int deth_qkey (struct rxe_pkt_info*) ; 
 scalar_t__ pkey_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int,...) ; 
 scalar_t__ qp_type (struct rxe_qp*) ; 
 int /*<<< orphan*/  set_bad_pkey_cntr (struct rxe_port*) ; 
 int /*<<< orphan*/  set_qkey_viol_cntr (struct rxe_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int check_keys(struct rxe_dev *rxe, struct rxe_pkt_info *pkt,
		      u32 qpn, struct rxe_qp *qp)
{
	int i;
	int found_pkey = 0;
	struct rxe_port *port = &rxe->port;
	u16 pkey = bth_pkey(pkt);

	pkt->pkey_index = 0;

	if (qpn == 1) {
		for (i = 0; i < port->attr.pkey_tbl_len; i++) {
			if (pkey_match(pkey, port->pkey_tbl[i])) {
				pkt->pkey_index = i;
				found_pkey = 1;
				break;
			}
		}

		if (!found_pkey) {
			pr_warn_ratelimited("bad pkey = 0x%x\n", pkey);
			set_bad_pkey_cntr(port);
			goto err1;
		}
	} else {
		if (unlikely(!pkey_match(pkey,
					 port->pkey_tbl[qp->attr.pkey_index]
					))) {
			pr_warn_ratelimited("bad pkey = 0x%0x\n", pkey);
			set_bad_pkey_cntr(port);
			goto err1;
		}
		pkt->pkey_index = qp->attr.pkey_index;
	}

	if ((qp_type(qp) == IB_QPT_UD || qp_type(qp) == IB_QPT_GSI) &&
	    pkt->mask) {
		u32 qkey = (qpn == 1) ? GSI_QKEY : qp->attr.qkey;

		if (unlikely(deth_qkey(pkt) != qkey)) {
			pr_warn_ratelimited("bad qkey, got 0x%x expected 0x%x for qpn 0x%x\n",
					    deth_qkey(pkt), qkey, qpn);
			set_qkey_viol_cntr(port);
			goto err1;
		}
	}

	return 0;

err1:
	return -EINVAL;
}
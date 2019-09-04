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
struct TYPE_3__ {int resid; } ;
struct rxe_send_wqe {int first_psn; int last_psn; TYPE_1__ dma; } ;
struct TYPE_4__ {int psn; } ;
struct rxe_qp {int mtu; TYPE_2__ req; } ;
struct rxe_pkt_info {int mask; } ;

/* Variables and functions */
 int BTH_PSN_MASK ; 
 int RXE_READ_MASK ; 
 int RXE_START_MASK ; 

__attribute__((used)) static void update_wqe_psn(struct rxe_qp *qp,
			   struct rxe_send_wqe *wqe,
			   struct rxe_pkt_info *pkt,
			   int payload)
{
	/* number of packets left to send including current one */
	int num_pkt = (wqe->dma.resid + payload + qp->mtu - 1) / qp->mtu;

	/* handle zero length packet case */
	if (num_pkt == 0)
		num_pkt = 1;

	if (pkt->mask & RXE_START_MASK) {
		wqe->first_psn = qp->req.psn;
		wqe->last_psn = (qp->req.psn + num_pkt - 1) & BTH_PSN_MASK;
	}

	if (pkt->mask & RXE_READ_MASK)
		qp->req.psn = (wqe->first_psn + num_pkt) & BTH_PSN_MASK;
	else
		qp->req.psn = (qp->req.psn + 1) & BTH_PSN_MASK;
}
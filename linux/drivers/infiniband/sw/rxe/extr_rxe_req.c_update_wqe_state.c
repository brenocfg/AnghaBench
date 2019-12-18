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
struct rxe_send_wqe {int /*<<< orphan*/  state; } ;
struct rxe_qp {int dummy; } ;
struct rxe_pkt_info {int mask; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 int RXE_END_MASK ; 
 scalar_t__ qp_type (struct rxe_qp*) ; 
 int /*<<< orphan*/  wqe_state_pending ; 
 int /*<<< orphan*/  wqe_state_processing ; 

__attribute__((used)) static void update_wqe_state(struct rxe_qp *qp,
		struct rxe_send_wqe *wqe,
		struct rxe_pkt_info *pkt)
{
	if (pkt->mask & RXE_END_MASK) {
		if (qp_type(qp) == IB_QPT_RC)
			wqe->state = wqe_state_pending;
	} else {
		wqe->state = wqe_state_processing;
	}
}
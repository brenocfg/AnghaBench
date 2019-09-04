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
typedef  int u32 ;
struct rvt_qp {int r_nak_state; int r_msn; int remote_qpn; int /*<<< orphan*/  r_ack_psn; } ;
struct TYPE_2__ {void* aeth; } ;
struct ib_other_headers {void** bth; TYPE_1__ u; } ;

/* Variables and functions */
 int IB_AETH_CREDIT_SHIFT ; 
 int IB_MSN_MASK ; 
 void* cpu_to_be32 (int) ; 
 int mask_psn (int /*<<< orphan*/ ) ; 
 void* rvt_compute_aeth (struct rvt_qp*) ; 

__attribute__((used)) static inline void hfi1_make_bth_aeth(struct rvt_qp *qp,
				      struct ib_other_headers *ohdr,
				      u32 bth0, u32 bth1)
{
	if (qp->r_nak_state)
		ohdr->u.aeth = cpu_to_be32((qp->r_msn & IB_MSN_MASK) |
					    (qp->r_nak_state <<
					     IB_AETH_CREDIT_SHIFT));
	else
		ohdr->u.aeth = rvt_compute_aeth(qp);

	ohdr->bth[0] = cpu_to_be32(bth0);
	ohdr->bth[1] = cpu_to_be32(bth1 | qp->remote_qpn);
	ohdr->bth[2] = cpu_to_be32(mask_psn(qp->r_ack_psn));
}
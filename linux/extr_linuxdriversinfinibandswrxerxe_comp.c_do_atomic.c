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
typedef  int /*<<< orphan*/  u64 ;
struct rxe_send_wqe {int /*<<< orphan*/  dma; } ;
struct rxe_qp {int /*<<< orphan*/  pd; } ;
struct rxe_pkt_info {int dummy; } ;
typedef  enum comp_state { ____Placeholder_comp_state } comp_state ;

/* Variables and functions */
 int COMPST_COMP_ACK ; 
 int COMPST_ERROR ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 int /*<<< orphan*/  atmack_orig (struct rxe_pkt_info*) ; 
 int copy_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_mem_obj ; 

__attribute__((used)) static inline enum comp_state do_atomic(struct rxe_qp *qp,
					struct rxe_pkt_info *pkt,
					struct rxe_send_wqe *wqe)
{
	int ret;

	u64 atomic_orig = atmack_orig(pkt);

	ret = copy_data(qp->pd, IB_ACCESS_LOCAL_WRITE,
			&wqe->dma, &atomic_orig,
			sizeof(u64), to_mem_obj, NULL);
	if (ret)
		return COMPST_ERROR;
	else
		return COMPST_COMP_ACK;
}
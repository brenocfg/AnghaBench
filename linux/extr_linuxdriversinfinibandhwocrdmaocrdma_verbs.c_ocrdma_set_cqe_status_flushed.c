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
struct ocrdma_qp {scalar_t__ qp_type; } ;
struct ocrdma_cqe {void* flags_status_srcqpn; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_UD ; 
 int OCRDMA_CQE_STATUS_MASK ; 
 int OCRDMA_CQE_STATUS_SHIFT ; 
 int OCRDMA_CQE_UD_STATUS_MASK ; 
 int OCRDMA_CQE_UD_STATUS_SHIFT ; 
 int OCRDMA_CQE_WR_FLUSH_ERR ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ is_cqe_for_sq (struct ocrdma_cqe*) ; 
 int le32_to_cpu (void*) ; 

__attribute__((used)) static void ocrdma_set_cqe_status_flushed(struct ocrdma_qp *qp,
						struct ocrdma_cqe *cqe)
{
	if (is_cqe_for_sq(cqe)) {
		cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
				cqe->flags_status_srcqpn) &
					~OCRDMA_CQE_STATUS_MASK);
		cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
				cqe->flags_status_srcqpn) |
				(OCRDMA_CQE_WR_FLUSH_ERR <<
					OCRDMA_CQE_STATUS_SHIFT));
	} else {
		if (qp->qp_type == IB_QPT_UD || qp->qp_type == IB_QPT_GSI) {
			cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
					cqe->flags_status_srcqpn) &
						~OCRDMA_CQE_UD_STATUS_MASK);
			cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
					cqe->flags_status_srcqpn) |
					(OCRDMA_CQE_WR_FLUSH_ERR <<
						OCRDMA_CQE_UD_STATUS_SHIFT));
		} else {
			cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
					cqe->flags_status_srcqpn) &
						~OCRDMA_CQE_STATUS_MASK);
			cqe->flags_status_srcqpn = cpu_to_le32(le32_to_cpu(
					cqe->flags_status_srcqpn) |
					(OCRDMA_CQE_WR_FLUSH_ERR <<
						OCRDMA_CQE_STATUS_SHIFT));
		}
	}
}
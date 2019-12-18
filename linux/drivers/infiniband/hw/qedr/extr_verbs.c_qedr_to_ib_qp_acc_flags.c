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
struct qed_rdma_query_qp_out_params {scalar_t__ incoming_atomic_en; scalar_t__ incoming_rdma_read_en; scalar_t__ incoming_rdma_write_en; } ;

/* Variables and functions */
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 

__attribute__((used)) static int qedr_to_ib_qp_acc_flags(struct qed_rdma_query_qp_out_params *params)
{
	int ib_qp_acc_flags = 0;

	if (params->incoming_rdma_write_en)
		ib_qp_acc_flags |= IB_ACCESS_REMOTE_WRITE;
	if (params->incoming_rdma_read_en)
		ib_qp_acc_flags |= IB_ACCESS_REMOTE_READ;
	if (params->incoming_atomic_en)
		ib_qp_acc_flags |= IB_ACCESS_REMOTE_ATOMIC;
	ib_qp_acc_flags |= IB_ACCESS_LOCAL_WRITE;
	return ib_qp_acc_flags;
}
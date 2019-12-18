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

/* Variables and functions */
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int OCRDMA_QP_INB_RD ; 
 int OCRDMA_QP_INB_WR ; 

__attribute__((used)) static int ocrdma_to_ib_qp_acc_flags(int qp_cap_flags)
{
	int ib_qp_acc_flags = 0;

	if (qp_cap_flags & OCRDMA_QP_INB_WR)
		ib_qp_acc_flags |= IB_ACCESS_REMOTE_WRITE;
	if (qp_cap_flags & OCRDMA_QP_INB_RD)
		ib_qp_acc_flags |= IB_ACCESS_LOCAL_WRITE;
	return ib_qp_acc_flags;
}
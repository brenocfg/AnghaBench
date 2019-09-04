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
struct ocrdma_qp {size_t id; } ;
struct ocrdma_dev {struct ocrdma_qp** qp_tbl; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t OCRDMA_MAX_QP ; 

__attribute__((used)) static int ocrdma_add_qpn_map(struct ocrdma_dev *dev, struct ocrdma_qp *qp)
{
	int status = -EINVAL;

	if (qp->id < OCRDMA_MAX_QP && dev->qp_tbl[qp->id] == NULL) {
		dev->qp_tbl[qp->id] = qp;
		status = 0;
	}
	return status;
}
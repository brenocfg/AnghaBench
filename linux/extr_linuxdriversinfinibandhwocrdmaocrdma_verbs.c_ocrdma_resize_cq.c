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
struct ocrdma_cq {int max_hw_cqe; } ;
struct ib_udata {int dummy; } ;
struct ib_cq {int cqe; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ocrdma_cq* get_ocrdma_cq (struct ib_cq*) ; 

int ocrdma_resize_cq(struct ib_cq *ibcq, int new_cnt,
		     struct ib_udata *udata)
{
	int status = 0;
	struct ocrdma_cq *cq = get_ocrdma_cq(ibcq);

	if (new_cnt < 1 || new_cnt > cq->max_hw_cqe) {
		status = -EINVAL;
		return status;
	}
	ibcq->cqe = new_cnt;
	return status;
}
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
struct ehea_cqe {int type; int status; scalar_t__ header_length; } ;

/* Variables and functions */
 int EHEA_CQE_STAT_ERR_MASK ; 
 int EHEA_CQE_STAT_ERR_TCP ; 
 int EHEA_CQE_TYPE_RQ ; 
 int EINVAL ; 

__attribute__((used)) static inline int ehea_check_cqe(struct ehea_cqe *cqe, int *rq_num)
{
	*rq_num = (cqe->type & EHEA_CQE_TYPE_RQ) >> 5;
	if ((cqe->status & EHEA_CQE_STAT_ERR_MASK) == 0)
		return 0;
	if (((cqe->status & EHEA_CQE_STAT_ERR_TCP) != 0) &&
	    (cqe->header_length == 0))
		return 0;
	return -EINVAL;
}
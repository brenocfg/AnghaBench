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
struct t4_cqe {int dummy; } ;
struct t4_cq {size_t sw_cidx; struct t4_cqe* sw_queue; scalar_t__ sw_in_use; scalar_t__ error; } ;

/* Variables and functions */
 int ENODATA ; 
 int t4_next_hw_cqe (struct t4_cq*,struct t4_cqe**) ; 

__attribute__((used)) static inline int t4_next_cqe(struct t4_cq *cq, struct t4_cqe **cqe)
{
	int ret = 0;

	if (cq->error)
		ret = -ENODATA;
	else if (cq->sw_in_use)
		*cqe = &cq->sw_queue[cq->sw_cidx];
	else
		ret = t4_next_hw_cqe(cq, cqe);
	return ret;
}
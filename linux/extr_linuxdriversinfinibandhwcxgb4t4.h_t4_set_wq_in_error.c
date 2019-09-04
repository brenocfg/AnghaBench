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
typedef  scalar_t__ u32 ;
struct t4_wq {int* qp_errp; scalar_t__* srqidxp; } ;

/* Variables and functions */

__attribute__((used)) static inline void t4_set_wq_in_error(struct t4_wq *wq, u32 srqidx)
{
	if (srqidx)
		*wq->srqidxp = srqidx;
	*wq->qp_errp = 1;
}
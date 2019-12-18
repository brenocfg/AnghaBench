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
struct siw_sqe {int dummy; } ;
struct TYPE_2__ {size_t orq_size; } ;
struct siw_qp {size_t orq_put; TYPE_1__ attrs; struct siw_sqe* orq; } ;

/* Variables and functions */

__attribute__((used)) static inline struct siw_sqe *orq_get_tail(struct siw_qp *qp)
{
	return &qp->orq[qp->orq_put % qp->attrs.orq_size];
}
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
struct siw_sqe {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {size_t sq_size; } ;
struct siw_qp {size_t sq_get; TYPE_1__ attrs; struct siw_sqe* sendq; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int siw_sq_empty(struct siw_qp *qp)
{
	struct siw_sqe *sqe = &qp->sendq[qp->sq_get % qp->attrs.sq_size];

	return READ_ONCE(sqe->flags) == 0;
}
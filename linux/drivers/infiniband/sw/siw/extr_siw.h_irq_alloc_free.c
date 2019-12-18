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
struct TYPE_2__ {size_t irq_size; } ;
struct siw_qp {size_t irq_put; TYPE_1__ attrs; struct siw_sqe* irq; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct siw_sqe *irq_alloc_free(struct siw_qp *qp)
{
	struct siw_sqe *irq_e = &qp->irq[qp->irq_put % qp->attrs.irq_size];

	if (READ_ONCE(irq_e->flags) == 0) {
		qp->irq_put++;
		return irq_e;
	}
	return NULL;
}
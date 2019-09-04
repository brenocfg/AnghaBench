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
struct TYPE_2__ {scalar_t__ tail; scalar_t__ head; } ;
struct ocrdma_qp {TYPE_1__ sq; } ;

/* Variables and functions */

__attribute__((used)) static int is_hw_sq_empty(struct ocrdma_qp *qp)
{
	return (qp->sq.tail == qp->sq.head);
}
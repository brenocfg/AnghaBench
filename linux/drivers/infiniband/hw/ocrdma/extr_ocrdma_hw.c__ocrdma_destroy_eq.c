#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ created; } ;
struct ocrdma_eq {TYPE_1__ q; } ;
struct ocrdma_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QTYPE_EQ ; 
 int /*<<< orphan*/  ocrdma_free_q (struct ocrdma_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  ocrdma_mbx_delete_q (struct ocrdma_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ocrdma_destroy_eq(struct ocrdma_dev *dev, struct ocrdma_eq *eq)
{
	if (eq->q.created) {
		ocrdma_mbx_delete_q(dev, &eq->q, QTYPE_EQ);
		ocrdma_free_q(dev, &eq->q);
	}
}
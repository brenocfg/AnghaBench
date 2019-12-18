#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocrdma_mqe {int dummy; } ;
struct TYPE_3__ {int head; struct ocrdma_mqe* va; } ;
struct TYPE_4__ {TYPE_1__ sq; } ;
struct ocrdma_dev {TYPE_2__ mq; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ocrdma_mqe *ocrdma_get_mqe(struct ocrdma_dev *dev)
{
	return dev->mq.sq.va + (dev->mq.sq.head * sizeof(struct ocrdma_mqe));
}
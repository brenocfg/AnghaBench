#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocrdma_mqe {int dummy; } ;
struct TYPE_6__ {int tag; } ;
struct TYPE_4__ {void* va; } ;
struct TYPE_5__ {TYPE_1__ sq; } ;
struct ocrdma_dev {TYPE_3__ mqe_ctx; TYPE_2__ mq; } ;

/* Variables and functions */

__attribute__((used)) static inline void *ocrdma_get_mqe_rsp(struct ocrdma_dev *dev)
{
	return dev->mq.sq.va + (dev->mqe_ctx.tag * sizeof(struct ocrdma_mqe));
}
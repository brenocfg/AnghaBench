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
typedef  int /*<<< orphan*/  u32 ;
struct ib_wq_attr {int dummy; } ;
struct ib_wq {TYPE_2__* device; } ;
struct TYPE_3__ {int (* modify_wq ) (struct ib_wq*,struct ib_wq_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct ib_wq*,struct ib_wq_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ib_modify_wq(struct ib_wq *wq, struct ib_wq_attr *wq_attr,
		 u32 wq_attr_mask)
{
	int err;

	if (!wq->device->ops.modify_wq)
		return -EOPNOTSUPP;

	err = wq->device->ops.modify_wq(wq, wq_attr, wq_attr_mask, NULL);
	return err;
}
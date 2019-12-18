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
typedef  int /*<<< orphan*/  u32 ;
struct knav_range_info {unsigned int queue_base; unsigned int acc; int flags; TYPE_1__* kdev; } ;
struct knav_queue_inst {unsigned int id; unsigned int acc; int /*<<< orphan*/  descs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_DESCS_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RANGE_MULTI_QUEUE ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int knav_acc_init_queue(struct knav_range_info *range,
				struct knav_queue_inst *kq)
{
	unsigned id = kq->id - range->queue_base;

	kq->descs = devm_kcalloc(range->kdev->dev,
				 ACC_DESCS_MAX, sizeof(u32), GFP_KERNEL);
	if (!kq->descs)
		return -ENOMEM;

	kq->acc = range->acc;
	if ((range->flags & RANGE_MULTI_QUEUE) == 0)
		kq->acc += id;
	return 0;
}
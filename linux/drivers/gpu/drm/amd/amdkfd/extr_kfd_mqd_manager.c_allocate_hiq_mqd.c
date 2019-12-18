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
struct queue_properties {int dummy; } ;
struct kfd_mem_obj {int /*<<< orphan*/  cpu_ptr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  gtt_mem; } ;
struct kfd_dev {TYPE_2__* dqm; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu_ptr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  gtt_mem; } ;
struct TYPE_4__ {TYPE_1__ hiq_sdma_mqd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct kfd_mem_obj* kzalloc (int,int /*<<< orphan*/ ) ; 

struct kfd_mem_obj *allocate_hiq_mqd(struct kfd_dev *dev, struct queue_properties *q)
{
	struct kfd_mem_obj *mqd_mem_obj = NULL;

	mqd_mem_obj = kzalloc(sizeof(struct kfd_mem_obj), GFP_KERNEL);
	if (!mqd_mem_obj)
		return NULL;

	mqd_mem_obj->gtt_mem = dev->dqm->hiq_sdma_mqd.gtt_mem;
	mqd_mem_obj->gpu_addr = dev->dqm->hiq_sdma_mqd.gpu_addr;
	mqd_mem_obj->cpu_ptr = dev->dqm->hiq_sdma_mqd.cpu_ptr;

	return mqd_mem_obj;
}
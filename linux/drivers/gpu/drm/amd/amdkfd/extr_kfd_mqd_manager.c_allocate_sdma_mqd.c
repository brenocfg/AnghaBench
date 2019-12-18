#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct queue_properties {int sdma_engine_id; int sdma_queue_id; } ;
struct kfd_mem_obj {int /*<<< orphan*/ * cpu_ptr; scalar_t__ gpu_addr; void* gtt_mem; } ;
struct kfd_dev {TYPE_4__* dqm; TYPE_1__* device_info; } ;
struct TYPE_7__ {scalar_t__ cpu_ptr; scalar_t__ gpu_addr; scalar_t__ gtt_mem; } ;
struct TYPE_8__ {TYPE_3__ hiq_sdma_mqd; TYPE_2__** mqd_mgrs; } ;
struct TYPE_6__ {int mqd_size; } ;
struct TYPE_5__ {int num_sdma_queues_per_engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t KFD_MQD_TYPE_HIQ ; 
 size_t KFD_MQD_TYPE_SDMA ; 
 struct kfd_mem_obj* kzalloc (int,int /*<<< orphan*/ ) ; 

struct kfd_mem_obj *allocate_sdma_mqd(struct kfd_dev *dev,
					struct queue_properties *q)
{
	struct kfd_mem_obj *mqd_mem_obj = NULL;
	uint64_t offset;

	mqd_mem_obj = kzalloc(sizeof(struct kfd_mem_obj), GFP_KERNEL);
	if (!mqd_mem_obj)
		return NULL;

	offset = (q->sdma_engine_id *
		dev->device_info->num_sdma_queues_per_engine +
		q->sdma_queue_id) *
		dev->dqm->mqd_mgrs[KFD_MQD_TYPE_SDMA]->mqd_size;

	offset += dev->dqm->mqd_mgrs[KFD_MQD_TYPE_HIQ]->mqd_size;

	mqd_mem_obj->gtt_mem = (void *)((uint64_t)dev->dqm->hiq_sdma_mqd.gtt_mem
				+ offset);
	mqd_mem_obj->gpu_addr = dev->dqm->hiq_sdma_mqd.gpu_addr + offset;
	mqd_mem_obj->cpu_ptr = (uint32_t *)((uint64_t)
				dev->dqm->hiq_sdma_mqd.cpu_ptr + offset);

	return mqd_mem_obj;
}
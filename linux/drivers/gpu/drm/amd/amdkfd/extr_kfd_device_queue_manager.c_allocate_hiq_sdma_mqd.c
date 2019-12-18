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
typedef  int uint32_t ;
struct kfd_mem_obj {int /*<<< orphan*/  cpu_ptr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  gtt_mem; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; TYPE_1__* device_info; } ;
struct device_queue_manager {TYPE_2__** mqd_mgrs; struct kfd_mem_obj hiq_sdma_mqd; struct kfd_dev* dev; } ;
struct TYPE_4__ {int mqd_size; } ;
struct TYPE_3__ {int num_sdma_engines; int num_sdma_queues_per_engine; } ;

/* Variables and functions */
 size_t KFD_MQD_TYPE_HIQ ; 
 size_t KFD_MQD_TYPE_SDMA ; 
 int amdgpu_amdkfd_alloc_gtt_mem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static int allocate_hiq_sdma_mqd(struct device_queue_manager *dqm)
{
	int retval;
	struct kfd_dev *dev = dqm->dev;
	struct kfd_mem_obj *mem_obj = &dqm->hiq_sdma_mqd;
	uint32_t size = dqm->mqd_mgrs[KFD_MQD_TYPE_SDMA]->mqd_size *
		dev->device_info->num_sdma_engines *
		dev->device_info->num_sdma_queues_per_engine +
		dqm->mqd_mgrs[KFD_MQD_TYPE_HIQ]->mqd_size;

	retval = amdgpu_amdkfd_alloc_gtt_mem(dev->kgd, size,
		&(mem_obj->gtt_mem), &(mem_obj->gpu_addr),
		(void *)&(mem_obj->cpu_ptr), true);

	return retval;
}
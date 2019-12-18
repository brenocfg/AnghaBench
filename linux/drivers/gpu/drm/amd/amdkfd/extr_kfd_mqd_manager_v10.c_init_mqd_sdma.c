#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct v10_sdma_mqd {int dummy; } ;
struct queue_properties {int dummy; } ;
struct mqd_manager {int /*<<< orphan*/  (* update_mqd ) (struct mqd_manager*,struct v10_sdma_mqd*,struct queue_properties*) ;} ;
struct kfd_mem_obj {int /*<<< orphan*/  gpu_addr; scalar_t__ cpu_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct v10_sdma_mqd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct mqd_manager*,struct v10_sdma_mqd*,struct queue_properties*) ; 

__attribute__((used)) static void init_mqd_sdma(struct mqd_manager *mm, void **mqd,
		struct kfd_mem_obj *mqd_mem_obj, uint64_t *gart_addr,
		struct queue_properties *q)
{
	struct v10_sdma_mqd *m;

	m = (struct v10_sdma_mqd *) mqd_mem_obj->cpu_ptr;

	memset(m, 0, sizeof(struct v10_sdma_mqd));

	*mqd = m;
	if (gart_addr)
		*gart_addr = mqd_mem_obj->gpu_addr;

	mm->update_mqd(mm, m, q);
}
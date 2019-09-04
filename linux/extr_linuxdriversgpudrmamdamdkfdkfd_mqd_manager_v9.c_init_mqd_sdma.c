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
struct v9_sdma_mqd {int dummy; } ;
struct queue_properties {int dummy; } ;
struct mqd_manager {int (* update_mqd ) (struct mqd_manager*,struct v9_sdma_mqd*,struct queue_properties*) ;int /*<<< orphan*/  dev; } ;
struct kfd_mem_obj {int /*<<< orphan*/  gpu_addr; scalar_t__ cpu_ptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int kfd_gtt_sa_allocate (int /*<<< orphan*/ ,int,struct kfd_mem_obj**) ; 
 int /*<<< orphan*/  memset (struct v9_sdma_mqd*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct mqd_manager*,struct v9_sdma_mqd*,struct queue_properties*) ; 

__attribute__((used)) static int init_mqd_sdma(struct mqd_manager *mm, void **mqd,
		struct kfd_mem_obj **mqd_mem_obj, uint64_t *gart_addr,
		struct queue_properties *q)
{
	int retval;
	struct v9_sdma_mqd *m;


	retval = kfd_gtt_sa_allocate(mm->dev,
			sizeof(struct v9_sdma_mqd),
			mqd_mem_obj);

	if (retval != 0)
		return -ENOMEM;

	m = (struct v9_sdma_mqd *) (*mqd_mem_obj)->cpu_ptr;

	memset(m, 0, sizeof(struct v9_sdma_mqd));

	*mqd = m;
	if (gart_addr)
		*gart_addr = (*mqd_mem_obj)->gpu_addr;

	retval = mm->update_mqd(mm, m, q);

	return retval;
}
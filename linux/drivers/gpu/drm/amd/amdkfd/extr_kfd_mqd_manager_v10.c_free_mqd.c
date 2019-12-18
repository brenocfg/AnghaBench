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
struct mqd_manager {struct kfd_dev* dev; } ;
struct kfd_mem_obj {scalar_t__ gtt_mem; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_amdkfd_free_gtt_mem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfd_gtt_sa_free (struct kfd_dev*,struct kfd_mem_obj*) ; 
 int /*<<< orphan*/  kfree (struct kfd_mem_obj*) ; 

__attribute__((used)) static void free_mqd(struct mqd_manager *mm, void *mqd,
			struct kfd_mem_obj *mqd_mem_obj)
{
	struct kfd_dev *kfd = mm->dev;

	if (mqd_mem_obj->gtt_mem) {
		amdgpu_amdkfd_free_gtt_mem(kfd->kgd, mqd_mem_obj->gtt_mem);
		kfree(mqd_mem_obj);
	} else {
		kfd_gtt_sa_free(mm->dev, mqd_mem_obj);
	}
}
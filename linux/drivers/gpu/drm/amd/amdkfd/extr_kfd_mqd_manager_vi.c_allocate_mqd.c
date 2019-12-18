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
struct vi_mqd {int dummy; } ;
struct queue_properties {int dummy; } ;
struct kfd_mem_obj {int dummy; } ;
struct kfd_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ kfd_gtt_sa_allocate (struct kfd_dev*,int,struct kfd_mem_obj**) ; 

__attribute__((used)) static struct kfd_mem_obj *allocate_mqd(struct kfd_dev *kfd,
					struct queue_properties *q)
{
	struct kfd_mem_obj *mqd_mem_obj;

	if (kfd_gtt_sa_allocate(kfd, sizeof(struct vi_mqd),
			&mqd_mem_obj))
		return NULL;

	return mqd_mem_obj;
}
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
struct queue_properties {int dummy; } ;
struct mqd_manager {int dummy; } ;
struct kfd_mem_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_mqd (struct mqd_manager*,void**,struct kfd_mem_obj*,int /*<<< orphan*/ *,struct queue_properties*) ; 

__attribute__((used)) static void init_mqd_hiq(struct mqd_manager *mm, void **mqd,
		struct kfd_mem_obj *mqd_mem_obj, uint64_t *gart_addr,
		struct queue_properties *q)
{
	init_mqd(mm, mqd, mqd_mem_obj, gart_addr, q);
}
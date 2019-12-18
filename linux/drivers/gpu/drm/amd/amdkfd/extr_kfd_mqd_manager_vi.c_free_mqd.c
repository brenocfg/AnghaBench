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
struct mqd_manager {int /*<<< orphan*/  dev; } ;
struct kfd_mem_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfd_gtt_sa_free (int /*<<< orphan*/ ,struct kfd_mem_obj*) ; 

__attribute__((used)) static void free_mqd(struct mqd_manager *mm, void *mqd,
			struct kfd_mem_obj *mqd_mem_obj)
{
	kfd_gtt_sa_free(mm->dev, mqd_mem_obj);
}
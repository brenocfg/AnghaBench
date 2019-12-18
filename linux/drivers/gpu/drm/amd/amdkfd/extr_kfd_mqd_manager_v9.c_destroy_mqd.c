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
typedef  int /*<<< orphan*/  uint32_t ;
struct mqd_manager {TYPE_2__* dev; } ;
typedef  enum kfd_preempt_type { ____Placeholder_kfd_preempt_type } kfd_preempt_type ;
struct TYPE_4__ {int /*<<< orphan*/  kgd; TYPE_1__* kfd2kgd; } ;
struct TYPE_3__ {int (* hqd_destroy ) (int /*<<< orphan*/ ,void*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,void*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int destroy_mqd(struct mqd_manager *mm, void *mqd,
			enum kfd_preempt_type type,
			unsigned int timeout, uint32_t pipe_id,
			uint32_t queue_id)
{
	return mm->dev->kfd2kgd->hqd_destroy
		(mm->dev->kgd, mqd, type, timeout,
		pipe_id, queue_id);
}
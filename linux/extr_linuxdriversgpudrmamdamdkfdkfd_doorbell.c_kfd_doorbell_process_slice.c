#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kfd_dev {TYPE_1__* device_info; } ;
struct TYPE_2__ {int doorbell_size; } ;

/* Variables and functions */
 int KFD_MAX_NUM_OF_QUEUES_PER_PROCESS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t roundup (int,int /*<<< orphan*/ ) ; 

size_t kfd_doorbell_process_slice(struct kfd_dev *kfd)
{
	return roundup(kfd->device_info->doorbell_size *
			KFD_MAX_NUM_OF_QUEUES_PER_PROCESS,
			PAGE_SIZE);
}
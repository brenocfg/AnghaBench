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
struct device_queue_manager {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* device_info; } ;
struct TYPE_3__ {unsigned int num_sdma_engines; } ;

/* Variables and functions */
 unsigned int KFD_SDMA_QUEUES_PER_ENGINE ; 

unsigned int get_num_sdma_queues(struct device_queue_manager *dqm)
{
	return dqm->dev->device_info->num_sdma_engines
			* KFD_SDMA_QUEUES_PER_ENGINE;
}
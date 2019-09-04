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
struct TYPE_3__ {int /*<<< orphan*/  queue_bitmap; } ;
struct TYPE_4__ {TYPE_1__ shared_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  KGD_MAX_QUEUES ; 
 unsigned int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int get_queues_num(struct device_queue_manager *dqm)
{
	return bitmap_weight(dqm->dev->shared_resources.queue_bitmap,
				KGD_MAX_QUEUES);
}
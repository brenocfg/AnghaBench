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

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_MAX_DEPTH ; 
 int /*<<< orphan*/  DM_MQ_QUEUE_DEPTH ; 
 int __dm_get_module_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_mq_queue_depth ; 

__attribute__((used)) static unsigned dm_get_blk_mq_queue_depth(void)
{
	return __dm_get_module_param(&dm_mq_queue_depth,
				     DM_MQ_QUEUE_DEPTH, BLK_MQ_MAX_DEPTH);
}
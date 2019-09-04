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
 int __dm_get_module_param (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dm_mq_nr_hw_queues ; 

__attribute__((used)) static unsigned dm_get_blk_mq_nr_hw_queues(void)
{
	return __dm_get_module_param(&dm_mq_nr_hw_queues, 1, 32);
}
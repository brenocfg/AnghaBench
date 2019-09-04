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
struct mapped_device {int use_blk_mq; TYPE_2__* queue; } ;
struct TYPE_4__ {TYPE_1__* backing_dev_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  congested_fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_any_congested ; 

__attribute__((used)) static void dm_init_normal_md_queue(struct mapped_device *md)
{
	md->use_blk_mq = false;

	/*
	 * Initialize aspects of queue that aren't relevant for blk-mq
	 */
	md->queue->backing_dev_info->congested_fn = dm_any_congested;
}
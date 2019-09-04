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
struct mapped_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dm_mq_kick_requeue_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_get_md_queue (struct mapped_device*) ; 

void dm_mq_kick_requeue_list(struct mapped_device *md)
{
	__dm_mq_kick_requeue_list(dm_get_md_queue(md), 0);
}
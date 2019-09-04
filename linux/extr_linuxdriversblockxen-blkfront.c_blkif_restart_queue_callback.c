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
struct blkfront_ring_info {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blkif_restart_queue_callback(void *arg)
{
	struct blkfront_ring_info *rinfo = (struct blkfront_ring_info *)arg;
	schedule_work(&rinfo->work);
}
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
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_run_hw_queues (struct request_queue*,int) ; 

__attribute__((used)) static void scsi_kick_queue(struct request_queue *q)
{
	blk_mq_run_hw_queues(q, false);
}
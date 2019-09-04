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
struct request_queue {unsigned int rq_timeout; } ;

/* Variables and functions */

void blk_queue_rq_timeout(struct request_queue *q, unsigned int timeout)
{
	q->rq_timeout = timeout;
}
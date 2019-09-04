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
struct bfq_queue {int service_from_backlogged; TYPE_1__* bfqd; scalar_t__ last_idle_bklogged; int /*<<< orphan*/  soft_rt_next_start; } ;
struct bfq_data {int bfq_wr_max_softrt_rate; } ;
struct TYPE_2__ {int /*<<< orphan*/  bfq_slice_idle; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 unsigned long max3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ nsecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long bfq_bfqq_softrt_next_start(struct bfq_data *bfqd,
						struct bfq_queue *bfqq)
{
	return max3(bfqq->soft_rt_next_start,
		    bfqq->last_idle_bklogged +
		    HZ * bfqq->service_from_backlogged /
		    bfqd->bfq_wr_max_softrt_rate,
		    jiffies + nsecs_to_jiffies(bfqq->bfqd->bfq_slice_idle) + 4);
}
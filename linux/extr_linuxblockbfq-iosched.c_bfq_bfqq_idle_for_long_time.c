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
struct bfq_queue {scalar_t__ dispatched; scalar_t__ budget_timeout; } ;
struct bfq_data {scalar_t__ bfq_wr_min_idle_time; } ;

/* Variables and functions */
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static bool bfq_bfqq_idle_for_long_time(struct bfq_data *bfqd,
					struct bfq_queue *bfqq)
{
	return bfqq->dispatched == 0 &&
		time_is_before_jiffies(
			bfqq->budget_timeout +
			bfqd->bfq_wr_min_idle_time);
}
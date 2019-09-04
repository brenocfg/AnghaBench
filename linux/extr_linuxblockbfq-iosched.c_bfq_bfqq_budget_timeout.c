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
struct bfq_queue {int /*<<< orphan*/  budget_timeout; } ;

/* Variables and functions */
 int time_is_before_eq_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bfq_bfqq_budget_timeout(struct bfq_queue *bfqq)
{
	return time_is_before_eq_jiffies(bfqq->budget_timeout);
}
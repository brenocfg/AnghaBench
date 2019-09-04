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
struct bfq_queue {int /*<<< orphan*/  wr_start_at_switch_to_srt; int /*<<< orphan*/  last_wr_start_finish; int /*<<< orphan*/  wr_cur_max_time; int /*<<< orphan*/  wr_coeff; } ;
struct bfq_data {int /*<<< orphan*/  bfq_wr_coeff; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_wr_duration (struct bfq_data*) ; 

__attribute__((used)) static void switch_back_to_interactive_wr(struct bfq_queue *bfqq,
					  struct bfq_data *bfqd)
{
	bfqq->wr_coeff = bfqd->bfq_wr_coeff;
	bfqq->wr_cur_max_time = bfq_wr_duration(bfqd);
	bfqq->last_wr_start_finish = bfqq->wr_start_at_switch_to_srt;
}
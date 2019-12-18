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
struct sdebug_queued_cmd {int /*<<< orphan*/ * sd_dp; } ;
struct sdebug_queue {struct sdebug_queued_cmd* qc_arr; } ;

/* Variables and functions */
 int SDEBUG_CANQUEUE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct sdebug_queue* sdebug_q_arr ; 
 int submit_queues ; 

__attribute__((used)) static void free_all_queued(void)
{
	int j, k;
	struct sdebug_queue *sqp;
	struct sdebug_queued_cmd *sqcp;

	for (j = 0, sqp = sdebug_q_arr; j < submit_queues; ++j, ++sqp) {
		for (k = 0; k < SDEBUG_CANQUEUE; ++k) {
			sqcp = &sqp->qc_arr[k];
			kfree(sqcp->sd_dp);
			sqcp->sd_dp = NULL;
		}
	}
}
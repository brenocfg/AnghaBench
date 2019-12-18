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
struct mmc_queue {int* in_flight; } ;

/* Variables and functions */
 size_t MMC_ISSUE_ASYNC ; 
 size_t MMC_ISSUE_DCMD ; 
 size_t MMC_ISSUE_SYNC ; 

__attribute__((used)) static inline int mmc_tot_in_flight(struct mmc_queue *mq)
{
	return mq->in_flight[MMC_ISSUE_SYNC] +
	       mq->in_flight[MMC_ISSUE_DCMD] +
	       mq->in_flight[MMC_ISSUE_ASYNC];
}
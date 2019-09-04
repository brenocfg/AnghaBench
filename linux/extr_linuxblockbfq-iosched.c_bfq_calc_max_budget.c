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
typedef  unsigned long u64 ;
struct bfq_data {int /*<<< orphan*/  bfq_timeout; scalar_t__ peak_rate; } ;

/* Variables and functions */
 unsigned long BFQ_RATE_SHIFT ; 
 unsigned long USEC_PER_MSEC ; 
 unsigned long jiffies_to_msecs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long bfq_calc_max_budget(struct bfq_data *bfqd)
{
	return (u64)bfqd->peak_rate * USEC_PER_MSEC *
		jiffies_to_msecs(bfqd->bfq_timeout)>>BFQ_RATE_SHIFT;
}
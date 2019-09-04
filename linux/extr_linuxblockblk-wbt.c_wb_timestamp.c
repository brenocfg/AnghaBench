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
struct rq_wb {int dummy; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 scalar_t__ rwb_enabled (struct rq_wb*) ; 

__attribute__((used)) static void wb_timestamp(struct rq_wb *rwb, unsigned long *var)
{
	if (rwb_enabled(rwb)) {
		const unsigned long cur = jiffies;

		if (cur != *var)
			*var = cur;
	}
}
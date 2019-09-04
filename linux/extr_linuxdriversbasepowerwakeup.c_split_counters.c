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

/* Variables and functions */
 unsigned int IN_PROGRESS_BITS ; 
 unsigned int MAX_IN_PROGRESS ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  combined_event_count ; 

__attribute__((used)) static void split_counters(unsigned int *cnt, unsigned int *inpr)
{
	unsigned int comb = atomic_read(&combined_event_count);

	*cnt = (comb >> IN_PROGRESS_BITS);
	*inpr = comb & MAX_IN_PROGRESS;
}
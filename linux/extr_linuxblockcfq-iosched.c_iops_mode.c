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
struct cfq_data {scalar_t__ hw_tag; int /*<<< orphan*/  cfq_slice_idle; } ;

/* Variables and functions */

__attribute__((used)) static inline bool iops_mode(struct cfq_data *cfqd)
{
	/*
	 * If we are not idling on queues and it is a NCQ drive, parallel
	 * execution of requests is on and measuring time is not possible
	 * in most of the cases until and unless we drive shallower queue
	 * depths and that becomes a performance bottleneck. In such cases
	 * switch to start providing fairness in terms of number of IOs.
	 */
	if (!cfqd->cfq_slice_idle && cfqd->hw_tag)
		return true;
	else
		return false;
}
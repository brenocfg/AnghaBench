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
typedef  scalar_t__ u64 ;
struct cfq_ttime {scalar_t__ ttime_mean; int /*<<< orphan*/  ttime_samples; } ;
struct cfq_data {scalar_t__ cfq_group_idle; scalar_t__ cfq_slice_idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  sample_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool cfq_io_thinktime_big(struct cfq_data *cfqd,
	struct cfq_ttime *ttime, bool group_idle)
{
	u64 slice;
	if (!sample_valid(ttime->ttime_samples))
		return false;
	if (group_idle)
		slice = cfqd->cfq_group_idle;
	else
		slice = cfqd->cfq_slice_idle;
	return ttime->ttime_mean > slice;
}
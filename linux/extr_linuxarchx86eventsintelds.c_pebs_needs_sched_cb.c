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
struct cpu_hw_events {scalar_t__ n_pebs; scalar_t__ n_large_pebs; } ;

/* Variables and functions */

__attribute__((used)) static inline bool pebs_needs_sched_cb(struct cpu_hw_events *cpuc)
{
	return cpuc->n_pebs && (cpuc->n_pebs == cpuc->n_large_pebs);
}
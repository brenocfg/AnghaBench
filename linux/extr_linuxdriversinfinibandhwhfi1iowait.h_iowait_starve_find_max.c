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
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ u8 ;
struct iowait {scalar_t__ starved_cnt; } ;

/* Variables and functions */

__attribute__((used)) static inline void iowait_starve_find_max(struct iowait *w, u8 *max,
					  uint idx, uint *max_idx)
{
	if (w->starved_cnt > *max) {
		*max = w->starved_cnt;
		*max_idx = idx;
	}
}
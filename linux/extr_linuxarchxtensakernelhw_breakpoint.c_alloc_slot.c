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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 

__attribute__((used)) static int alloc_slot(struct perf_event **slot, size_t n,
		      struct perf_event *bp)
{
	size_t i;

	for (i = 0; i < n; ++i) {
		if (!slot[i]) {
			slot[i] = bp;
			return i;
		}
	}
	return -EBUSY;
}
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
struct sf_buffer {scalar_t__ num_sdb; int /*<<< orphan*/  sdbt; } ;
struct hw_perf_event {int dummy; } ;

/* Variables and functions */
 unsigned long SFB_ALLOC_REG (struct hw_perf_event*) ; 

__attribute__((used)) static unsigned long sfb_pending_allocs(struct sf_buffer *sfb,
					struct hw_perf_event *hwc)
{
	if (!sfb->sdbt)
		return SFB_ALLOC_REG(hwc);
	if (SFB_ALLOC_REG(hwc) > sfb->num_sdb)
		return SFB_ALLOC_REG(hwc) - sfb->num_sdb;
	return 0;
}
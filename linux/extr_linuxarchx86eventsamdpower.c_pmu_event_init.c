#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_3__ {scalar_t__ config; scalar_t__ type; scalar_t__ sample_period; scalar_t__ exclude_guest; scalar_t__ exclude_host; scalar_t__ exclude_idle; scalar_t__ exclude_hv; scalar_t__ exclude_kernel; scalar_t__ exclude_user; } ;
struct perf_event {TYPE_1__ attr; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AMD_POWER_EVENTSEL_PKG ; 
 scalar_t__ AMD_POWER_EVENT_MASK ; 
 int EINVAL ; 
 int ENOENT ; 
 TYPE_2__ pmu_class ; 

__attribute__((used)) static int pmu_event_init(struct perf_event *event)
{
	u64 cfg = event->attr.config & AMD_POWER_EVENT_MASK;

	/* Only look at AMD power events. */
	if (event->attr.type != pmu_class.type)
		return -ENOENT;

	/* Unsupported modes and filters. */
	if (event->attr.exclude_user   ||
	    event->attr.exclude_kernel ||
	    event->attr.exclude_hv     ||
	    event->attr.exclude_idle   ||
	    event->attr.exclude_host   ||
	    event->attr.exclude_guest  ||
	    /* no sampling */
	    event->attr.sample_period)
		return -EINVAL;

	if (cfg != AMD_POWER_EVENTSEL_PKG)
		return -EINVAL;

	return 0;
}
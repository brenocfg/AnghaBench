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
struct TYPE_3__ {int config; } ;
struct TYPE_4__ {scalar_t__ exclude_guest; scalar_t__ exclude_host; } ;
struct perf_event {TYPE_1__ hw; TYPE_2__ attr; } ;

/* Variables and functions */
 int AMD64_EVENTSEL_GUESTONLY ; 
 int AMD64_EVENTSEL_HOSTONLY ; 
 int ARCH_PERFMON_EVENTSEL_OS ; 
 int ARCH_PERFMON_EVENTSEL_USR ; 

__attribute__((used)) static int amd_core_hw_config(struct perf_event *event)
{
	if (event->attr.exclude_host && event->attr.exclude_guest)
		/*
		 * When HO == GO == 1 the hardware treats that as GO == HO == 0
		 * and will count in both modes. We don't want to count in that
		 * case so we emulate no-counting by setting US = OS = 0.
		 */
		event->hw.config &= ~(ARCH_PERFMON_EVENTSEL_USR |
				      ARCH_PERFMON_EVENTSEL_OS);
	else if (event->attr.exclude_host)
		event->hw.config |= AMD64_EVENTSEL_GUESTONLY;
	else if (event->attr.exclude_guest)
		event->hw.config |= AMD64_EVENTSEL_HOSTONLY;

	return 0;
}
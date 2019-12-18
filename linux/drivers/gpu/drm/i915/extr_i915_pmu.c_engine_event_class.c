#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int config; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int I915_PMU_CLASS_SHIFT ; 

__attribute__((used)) static u8 engine_event_class(struct perf_event *event)
{
	return (event->attr.config >> I915_PMU_CLASS_SHIFT) & 0xff;
}
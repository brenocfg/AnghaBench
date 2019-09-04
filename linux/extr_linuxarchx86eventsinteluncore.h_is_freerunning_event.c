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
typedef  int u64 ;
struct TYPE_2__ {int config; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int UNCORE_FIXED_EVENT ; 
 int UNCORE_FREERUNNING_UMASK_START ; 

__attribute__((used)) static inline bool is_freerunning_event(struct perf_event *event)
{
	u64 cfg = event->attr.config;

	return ((cfg & UNCORE_FIXED_EVENT) == UNCORE_FIXED_EVENT) &&
	       (((cfg >> 8) & 0xff) >= UNCORE_FREERUNNING_UMASK_START);
}
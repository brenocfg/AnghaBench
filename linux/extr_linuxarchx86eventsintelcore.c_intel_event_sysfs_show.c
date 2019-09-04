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
typedef  int u64 ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ARCH_PERFMON_EVENTSEL_EVENT ; 
 int /*<<< orphan*/  x86_event_sysfs_show (char*,int,int) ; 

ssize_t intel_event_sysfs_show(char *page, u64 config)
{
	u64 event = (config & ARCH_PERFMON_EVENTSEL_EVENT);

	return x86_event_sysfs_show(page, config, event);
}
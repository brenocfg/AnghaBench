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
struct apm_user {scalar_t__ event_tail; int /*<<< orphan*/ * events; } ;
typedef  int /*<<< orphan*/  apm_event_t ;

/* Variables and functions */
 scalar_t__ APM_MAX_EVENTS ; 

__attribute__((used)) static apm_event_t get_queued_event(struct apm_user *as)
{
	if (++as->event_tail >= APM_MAX_EVENTS)
		as->event_tail = 0;
	return as->events[as->event_tail];
}
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
typedef  int /*<<< orphan*/  apm_eventinfo_t ;
typedef  int apm_event_t ;

/* Variables and functions */
 int APM_NO_EVENTS ; 
 int APM_SUCCESS ; 
 int /*<<< orphan*/  apm_error (char*,int) ; 
 int apm_get_event (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apm_event_t get_event(void)
{
	int error;
	apm_event_t event = APM_NO_EVENTS; /* silence gcc */
	apm_eventinfo_t	info;

	static int notified;

	/* we don't use the eventinfo */
	error = apm_get_event(&event, &info);
	if (error == APM_SUCCESS)
		return event;

	if ((error != APM_NO_EVENTS) && (notified++ == 0))
		apm_error("get_event", error);

	return 0;
}
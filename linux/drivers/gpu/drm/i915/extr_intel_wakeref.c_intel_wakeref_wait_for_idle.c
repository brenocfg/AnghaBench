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
struct intel_wakeref {int /*<<< orphan*/  wakeref; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_wakeref_is_active (struct intel_wakeref*) ; 
 int wait_var_event_killable (int /*<<< orphan*/ *,int) ; 

int intel_wakeref_wait_for_idle(struct intel_wakeref *wf)
{
	return wait_var_event_killable(&wf->wakeref,
				       !intel_wakeref_is_active(wf));
}
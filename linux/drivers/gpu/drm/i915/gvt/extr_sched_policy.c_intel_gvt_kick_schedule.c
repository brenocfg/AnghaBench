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
struct intel_gvt {int /*<<< orphan*/  sched_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_GVT_REQUEST_EVENT_SCHED ; 
 int /*<<< orphan*/  intel_gvt_request_service (struct intel_gvt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_gvt_kick_schedule(struct intel_gvt *gvt)
{
	mutex_lock(&gvt->sched_lock);
	intel_gvt_request_service(gvt, INTEL_GVT_REQUEST_EVENT_SCHED);
	mutex_unlock(&gvt->sched_lock);
}
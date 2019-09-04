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
struct intel_dp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  edp_panel_on (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_lock (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_unlock (struct intel_dp*) ; 

void intel_edp_panel_on(struct intel_dp *intel_dp)
{
	if (!intel_dp_is_edp(intel_dp))
		return;

	pps_lock(intel_dp);
	edp_panel_on(intel_dp);
	pps_unlock(intel_dp);
}
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
struct intel_dp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* dp_to_dig_port (struct intel_dp*) ; 
 int edp_panel_vdd_on (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pps_lock (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_unlock (struct intel_dp*) ; 

void intel_edp_panel_vdd_on(struct intel_dp *intel_dp)
{
	bool vdd;

	if (!intel_dp_is_edp(intel_dp))
		return;

	pps_lock(intel_dp);
	vdd = edp_panel_vdd_on(intel_dp);
	pps_unlock(intel_dp);

	I915_STATE_WARN(!vdd, "eDP port %c VDD already requested on\n",
	     port_name(dp_to_dig_port(intel_dp)->base.port));
}
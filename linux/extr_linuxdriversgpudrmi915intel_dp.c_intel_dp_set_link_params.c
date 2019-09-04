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
typedef  int /*<<< orphan*/  uint8_t ;
struct intel_dp {int link_trained; int link_rate; int link_mst; int /*<<< orphan*/  lane_count; } ;

/* Variables and functions */

void intel_dp_set_link_params(struct intel_dp *intel_dp,
			      int link_rate, uint8_t lane_count,
			      bool link_mst)
{
	intel_dp->link_trained = false;
	intel_dp->link_rate = link_rate;
	intel_dp->lane_count = lane_count;
	intel_dp->link_mst = link_mst;
}
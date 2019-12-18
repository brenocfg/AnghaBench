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
struct intel_dp {int link_trained; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TRAINING_PATTERN_DISABLE ; 
 int /*<<< orphan*/  intel_dp_set_link_train (struct intel_dp*,int /*<<< orphan*/ ) ; 

void intel_dp_stop_link_train(struct intel_dp *intel_dp)
{
	intel_dp->link_trained = true;

	intel_dp_set_link_train(intel_dp,
				DP_TRAINING_PATTERN_DISABLE);
}
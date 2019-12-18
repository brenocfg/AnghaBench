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
typedef  int /*<<< orphan*/  u8 ;
struct intel_dp {int /*<<< orphan*/  train_set; } ;

/* Variables and functions */
 int intel_dp_set_link_train (struct intel_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_set_signal_levels (struct intel_dp*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
intel_dp_reset_link_train(struct intel_dp *intel_dp,
			u8 dp_train_pat)
{
	memset(intel_dp->train_set, 0, sizeof(intel_dp->train_set));
	intel_dp_set_signal_levels(intel_dp);
	return intel_dp_set_link_train(intel_dp, dp_train_pat);
}
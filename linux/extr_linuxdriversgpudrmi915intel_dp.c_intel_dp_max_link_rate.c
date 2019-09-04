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
struct intel_dp {int* common_rates; int /*<<< orphan*/  max_link_rate; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int intel_dp_common_len_rate_limit (struct intel_dp*,int /*<<< orphan*/ ) ; 

int
intel_dp_max_link_rate(struct intel_dp *intel_dp)
{
	int len;

	len = intel_dp_common_len_rate_limit(intel_dp, intel_dp->max_link_rate);
	if (WARN_ON(len <= 0))
		return 162000;

	return intel_dp->common_rates[len - 1];
}
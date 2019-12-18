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
struct intel_dp {int /*<<< orphan*/  num_common_rates; int /*<<< orphan*/  common_rates; } ;

/* Variables and functions */
 int intel_dp_rate_limit_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int intel_dp_common_len_rate_limit(const struct intel_dp *intel_dp,
					  int max_rate)
{
	return intel_dp_rate_limit_len(intel_dp->common_rates,
				       intel_dp->num_common_rates, max_rate);
}
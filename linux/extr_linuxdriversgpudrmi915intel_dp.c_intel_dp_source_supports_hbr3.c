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
struct intel_dp {int* source_rates; int num_source_rates; } ;

/* Variables and functions */

bool intel_dp_source_supports_hbr3(struct intel_dp *intel_dp)
{
	int max_rate = intel_dp->source_rates[intel_dp->num_source_rates - 1];

	return max_rate >= 810000;
}
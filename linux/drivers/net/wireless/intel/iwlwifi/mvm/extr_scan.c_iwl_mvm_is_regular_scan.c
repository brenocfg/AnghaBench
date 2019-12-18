#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm_scan_params {int n_scan_plans; TYPE_1__* scan_plans; } ;
struct TYPE_2__ {int iterations; } ;

/* Variables and functions */

__attribute__((used)) static inline bool iwl_mvm_is_regular_scan(struct iwl_mvm_scan_params *params)
{
	return params->n_scan_plans == 1 &&
		params->scan_plans[0].iterations == 1;
}
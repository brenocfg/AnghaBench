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
struct smu_context {int dummy; } ;
typedef  enum amd_pm_state_type { ____Placeholder_amd_pm_state_type } amd_pm_state_type ;

/* Variables and functions */
 int POWER_STATE_TYPE_DEFAULT ; 

enum amd_pm_state_type smu_get_current_power_state(struct smu_context *smu)
{
	/* not support power state */
	return POWER_STATE_TYPE_DEFAULT;
}
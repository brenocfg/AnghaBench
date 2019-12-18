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
typedef  int /*<<< orphan*/  uint32_t ;
struct smu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_FAN_CTRL_AUTO ; 
 int /*<<< orphan*/  AMD_FAN_CTRL_MANUAL ; 
 int /*<<< orphan*/  SMU_FEATURE_FAN_CONTROL_BIT ; 
 int /*<<< orphan*/  smu_feature_is_enabled (struct smu_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
smu_v11_0_get_fan_control_mode(struct smu_context *smu)
{
	if (!smu_feature_is_enabled(smu, SMU_FEATURE_FAN_CONTROL_BIT))
		return AMD_FAN_CTRL_MANUAL;
	else
		return AMD_FAN_CTRL_AUTO;
}
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
struct radeon_device {int dummy; } ;
struct kv_power_info {int /*<<< orphan*/  sram_end; int /*<<< orphan*/  graphics_dpm_level_count; scalar_t__ dpm_table_start; int /*<<< orphan*/  graphics_level; } ;
typedef  int /*<<< orphan*/  SMU7_Fusion_GraphicsLevel ;

/* Variables and functions */
 int /*<<< orphan*/  GraphicsDpmLevelCount ; 
 int /*<<< orphan*/  GraphicsLevel ; 
 int /*<<< orphan*/  SMU7_Fusion_DpmTable ; 
 int SMU7_MAX_LEVELS_GRAPHICS ; 
 int kv_copy_bytes_to_smc (struct radeon_device*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_upload_dpm_settings(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	int ret;

	ret = kv_copy_bytes_to_smc(rdev,
				   pi->dpm_table_start +
				   offsetof(SMU7_Fusion_DpmTable, GraphicsLevel),
				   (u8 *)&pi->graphics_level,
				   sizeof(SMU7_Fusion_GraphicsLevel) * SMU7_MAX_LEVELS_GRAPHICS,
				   pi->sram_end);

	if (ret)
		return ret;

	ret = kv_copy_bytes_to_smc(rdev,
				   pi->dpm_table_start +
				   offsetof(SMU7_Fusion_DpmTable, GraphicsDpmLevelCount),
				   &pi->graphics_dpm_level_count,
				   sizeof(u8), pi->sram_end);

	return ret;
}
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
struct kv_power_info {int graphics_interval; int /*<<< orphan*/  sram_end; scalar_t__ dpm_table_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  GraphicsInterval ; 
 int /*<<< orphan*/  SMU7_Fusion_DpmTable ; 
 int kv_copy_bytes_to_smc (struct radeon_device*,scalar_t__,int*,int,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_set_dpm_interval(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	int ret;

	pi->graphics_interval = 1;

	ret = kv_copy_bytes_to_smc(rdev,
				   pi->dpm_table_start +
				   offsetof(SMU7_Fusion_DpmTable, GraphicsInterval),
				   &pi->graphics_interval,
				   sizeof(u8), pi->sram_end);

	return ret;
}
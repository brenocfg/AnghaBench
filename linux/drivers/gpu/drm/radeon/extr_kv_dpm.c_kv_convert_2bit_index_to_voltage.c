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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vid_mapping_table; } ;
struct kv_power_info {TYPE_1__ sys_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kv_convert_8bit_index_to_voltage (struct radeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ kv_convert_vid2_to_vid7 (struct radeon_device*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 

__attribute__((used)) static u16 kv_convert_2bit_index_to_voltage(struct radeon_device *rdev,
					    u32 vid_2bit)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	u32 vid_8bit = kv_convert_vid2_to_vid7(rdev,
					       &pi->sys_info.vid_mapping_table,
					       vid_2bit);

	return kv_convert_8bit_index_to_voltage(rdev, (u16)vid_8bit);
}
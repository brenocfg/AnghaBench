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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  vid_mapping_table; } ;
struct sumo_power_info {TYPE_1__ sys_info; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int sumo_convert_vid2_to_vid7 (struct radeon_device*,int /*<<< orphan*/ *,int) ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 

__attribute__((used)) static u16 sumo_convert_voltage_index_to_value(struct radeon_device *rdev,
					       u32 vid_2bit)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	u32 vid_7bit = sumo_convert_vid2_to_vid7(rdev, &pi->sys_info.vid_mapping_table, vid_2bit);

	if (vid_7bit > 0x7C)
		return 0;

	return (15500 - vid_7bit * 125 + 5) / 10;
}
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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct kv_power_info {TYPE_1__* graphics_level; scalar_t__ voltage_drop_t; } ;
struct TYPE_2__ {int /*<<< orphan*/  MinVddNb; scalar_t__ VoltageDownH; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kv_convert_2bit_index_to_voltage (struct radeon_device*,size_t) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int kv_set_vid(struct radeon_device *rdev, u32 index, u32 vid)
{
	struct kv_power_info *pi = kv_get_pi(rdev);

	pi->graphics_level[index].VoltageDownH = (u8)pi->voltage_drop_t;
	pi->graphics_level[index].MinVddNb =
		cpu_to_be32(kv_convert_2bit_index_to_voltage(rdev, vid));

	return 0;
}
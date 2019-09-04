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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct radeon_device {int dummy; } ;
struct kv_power_info {TYPE_1__* graphics_level; } ;
struct TYPE_2__ {int /*<<< orphan*/  AT; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int kv_set_at(struct radeon_device *rdev, u32 index, u32 at)
{
	struct kv_power_info *pi = kv_get_pi(rdev);

	pi->graphics_level[index].AT = cpu_to_be16((u16)at);

	return 0;
}
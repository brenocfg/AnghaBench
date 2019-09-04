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
struct radeon_device {int dummy; } ;
struct kv_power_info {scalar_t__ low_sclk_interrupt_t; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void kv_init_sclk_t(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);

	pi->low_sclk_interrupt_t = 0;
}
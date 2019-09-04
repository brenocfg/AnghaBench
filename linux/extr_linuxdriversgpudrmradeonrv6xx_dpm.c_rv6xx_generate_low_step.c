#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sclk; } ;
struct rv6xx_ps {TYPE_2__ low; } ;
struct TYPE_3__ {scalar_t__ low_sclk_index; } ;
struct rv6xx_power_info {TYPE_1__ hw; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rv6xx_generate_single_step (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 
 struct rv6xx_ps* rv6xx_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void rv6xx_generate_low_step(struct radeon_device *rdev,
				    struct radeon_ps *new_ps)
{
	struct rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	pi->hw.low_sclk_index = 0;
	rv6xx_generate_single_step(rdev,
				   new_state->low.sclk,
				   0);
}
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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
struct atom_clock_dividers {scalar_t__ enable_post_div; int /*<<< orphan*/  post_div; int /*<<< orphan*/  fb_div; int /*<<< orphan*/  ref_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_MEMORY_PLL_PARAM ; 
 int EINVAL ; 
 scalar_t__ radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 
 int /*<<< orphan*/  rv6xx_memory_clock_entry_enable_post_divider (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv6xx_memory_clock_entry_set_feedback_divider (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv6xx_memory_clock_entry_set_post_divider (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv6xx_memory_clock_entry_set_reference_divider (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rv6xx_program_mclk_stepping_entry(struct radeon_device *rdev,
					     u32 entry, u32 clock)
{
	struct atom_clock_dividers dividers;

	if (radeon_atom_get_clock_dividers(rdev, COMPUTE_MEMORY_PLL_PARAM, clock, false, &dividers))
	    return -EINVAL;


	rv6xx_memory_clock_entry_set_reference_divider(rdev, entry, dividers.ref_div);
	rv6xx_memory_clock_entry_set_feedback_divider(rdev, entry, dividers.fb_div);
	rv6xx_memory_clock_entry_set_post_divider(rdev, entry, dividers.post_div);

	if (dividers.enable_post_div)
		rv6xx_memory_clock_entry_enable_post_divider(rdev, entry, true);
	else
		rv6xx_memory_clock_entry_enable_post_divider(rdev, entry, false);

	return 0;
}
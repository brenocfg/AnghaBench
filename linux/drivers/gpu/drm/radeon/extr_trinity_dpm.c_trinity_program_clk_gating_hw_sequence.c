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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32_P (int const,int const,int const) ; 

__attribute__((used)) static void trinity_program_clk_gating_hw_sequence(struct radeon_device *rdev,
						   const u32 *seq, u32 count)
{
	u32 i, length = count * 3;

	for (i = 0; i < length; i += 3)
		WREG32_P(seq[i], seq[i+1], ~seq[i+2]);
}
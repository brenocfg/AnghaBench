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
 int /*<<< orphan*/  WREG32 (int const,int const) ; 

__attribute__((used)) static void trinity_program_override_mgpg_sequences(struct radeon_device *rdev,
						    const u32 *seq, u32 count)
{
	u32  i, length = count * 2;

	for (i = 0; i < length; i += 2)
		WREG32(seq[i], seq[i+1]);

}
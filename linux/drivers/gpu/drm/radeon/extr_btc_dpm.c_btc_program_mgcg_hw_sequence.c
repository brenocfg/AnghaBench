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
 int RREG32 (int const) ; 
 int /*<<< orphan*/  WREG32 (int const,int) ; 

void btc_program_mgcg_hw_sequence(struct radeon_device *rdev,
				  const u32 *sequence, u32 count)
{
	u32 i, length = count * 3;
	u32 tmp;

	for (i = 0; i < length; i+=3) {
		tmp = RREG32(sequence[i]);
		tmp &= ~sequence[i+2];
		tmp |= sequence[i+1] & sequence[i+2];
		WREG32(sequence[i], tmp);
	}
}
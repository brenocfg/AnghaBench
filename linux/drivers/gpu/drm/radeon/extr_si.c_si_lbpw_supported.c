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
 int /*<<< orphan*/  MC_SEQ_MISC0 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool si_lbpw_supported(struct radeon_device *rdev)
{
	u32 tmp;

	/* Enable LBPW only for DDR3 */
	tmp = RREG32(MC_SEQ_MISC0);
	if ((tmp & 0xF0000000) == 0xB0000000)
		return true;
	return false;
}
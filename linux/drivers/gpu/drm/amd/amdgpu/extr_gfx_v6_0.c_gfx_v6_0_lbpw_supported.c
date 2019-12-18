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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMC_SEQ_MISC0 ; 

__attribute__((used)) static bool gfx_v6_0_lbpw_supported(struct amdgpu_device *adev)
{
	u32 tmp;

	/* Enable LBPW only for DDR3 */
	tmp = RREG32(mmMC_SEQ_MISC0);
	if ((tmp & 0xF0000000) == 0xB0000000)
		return true;
	return false;
}
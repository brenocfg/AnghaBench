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
 int CAC_WINDOW_MASK ; 
 int /*<<< orphan*/  CG_CAC_CTRL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int amdgpu_asic_get_xclk (struct amdgpu_device*) ; 

__attribute__((used)) static u32 si_calculate_cac_wintime(struct amdgpu_device *adev)
{
	u32 xclk;
	u32 wintime;
	u32 cac_window;
	u32 cac_window_size;

	xclk = amdgpu_asic_get_xclk(adev);

	if (xclk == 0)
		return 0;

	cac_window = RREG32(CG_CAC_CTRL) & CAC_WINDOW_MASK;
	cac_window_size = ((cac_window & 0xFFFF0000) >> 16) * (cac_window & 0x0000FFFF);

	wintime = (cac_window_size * 100) / xclk;

	return wintime;
}
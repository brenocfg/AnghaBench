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
 int /*<<< orphan*/  MC_SHARED_CHMAP ; 
 int /*<<< orphan*/  NOOFCHAN ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMC_SHARED_CHMAP ; 

__attribute__((used)) static u32 cik_get_number_of_dram_channels(struct amdgpu_device *adev)
{
	u32 tmp = RREG32(mmMC_SHARED_CHMAP);

	switch (REG_GET_FIELD(tmp, MC_SHARED_CHMAP, NOOFCHAN)) {
	case 0:
	default:
		return 1;
	case 1:
		return 2;
	case 2:
		return 4;
	case 3:
		return 8;
	case 4:
		return 3;
	case 5:
		return 6;
	case 6:
		return 10;
	case 7:
		return 12;
	case 8:
		return 16;
	}
}
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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CNTL__VGA_DIS_MASK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCONFIG_CNTL ; 

__attribute__((used)) static void cik_vga_set_state(struct amdgpu_device *adev, bool state)
{
	uint32_t tmp;

	tmp = RREG32(mmCONFIG_CNTL);
	if (!state)
		tmp |= CONFIG_CNTL__VGA_DIS_MASK;
	else
		tmp &= ~CONFIG_CNTL__VGA_DIS_MASK;
	WREG32(mmCONFIG_CNTL, tmp);
}
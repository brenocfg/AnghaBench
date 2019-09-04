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
typedef  int uint32_t ;
struct psp_context {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK ; 
 int /*<<< orphan*/  NBIO ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmPCIE_DATA2 ; 
 int /*<<< orphan*/  mmPCIE_INDEX2 ; 
 int smnMP1_FIRMWARE_FLAGS ; 

__attribute__((used)) static bool psp_v3_1_smu_reload_quirk(struct psp_context *psp)
{
	struct amdgpu_device *adev = psp->adev;
	uint32_t reg;

	reg = smnMP1_FIRMWARE_FLAGS | 0x03b00000;
	WREG32_SOC15(NBIO, 0, mmPCIE_INDEX2, reg);
	reg = RREG32_SOC15(NBIO, 0, mmPCIE_DATA2);
	return (reg & MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK) ? true : false;
}
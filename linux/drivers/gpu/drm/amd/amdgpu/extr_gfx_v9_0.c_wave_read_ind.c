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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SQ_IND_INDEX__FORCE_READ_MASK ; 
 int SQ_IND_INDEX__INDEX__SHIFT ; 
 int SQ_IND_INDEX__SIMD_ID__SHIFT ; 
 int SQ_IND_INDEX__WAVE_ID__SHIFT ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmSQ_IND_DATA ; 
 int /*<<< orphan*/  mmSQ_IND_INDEX ; 

__attribute__((used)) static uint32_t wave_read_ind(struct amdgpu_device *adev, uint32_t simd, uint32_t wave, uint32_t address)
{
	WREG32_SOC15(GC, 0, mmSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(address << SQ_IND_INDEX__INDEX__SHIFT) |
		(SQ_IND_INDEX__FORCE_READ_MASK));
	return RREG32_SOC15(GC, 0, mmSQ_IND_DATA);
}
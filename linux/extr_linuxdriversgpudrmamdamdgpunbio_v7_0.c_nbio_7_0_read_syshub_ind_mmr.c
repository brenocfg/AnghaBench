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
 int /*<<< orphan*/  NBIO ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSYSHUB_DATA ; 
 int /*<<< orphan*/  mmSYSHUB_INDEX ; 

__attribute__((used)) static uint32_t nbio_7_0_read_syshub_ind_mmr(struct amdgpu_device *adev, uint32_t offset)
{
	uint32_t data;

	WREG32_SOC15(NBIO, 0, mmSYSHUB_INDEX, offset);
	data = RREG32_SOC15(NBIO, 0, mmSYSHUB_DATA);

	return data;
}
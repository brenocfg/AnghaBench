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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_PIPELINE_PG_ENABLE ; 
 int /*<<< orphan*/  RLC_PG_CNTL ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmDB_RENDER_CONTROL ; 

__attribute__((used)) static void cz_enable_gfx_pipeline_power_gating(struct amdgpu_device *adev,
						bool enable)
{
	WREG32_FIELD(RLC_PG_CNTL, GFX_PIPELINE_PG_ENABLE, enable ? 1 : 0);

	/* Read any GFX register to wake up GFX. */
	if (!enable)
		RREG32(mmDB_RENDER_CONTROL);
}
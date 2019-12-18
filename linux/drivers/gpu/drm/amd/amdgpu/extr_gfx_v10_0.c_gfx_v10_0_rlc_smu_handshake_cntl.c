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
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmRLC_PG_CNTL ; 

__attribute__((used)) static void gfx_v10_0_rlc_smu_handshake_cntl(struct amdgpu_device *adev,
					     bool enable)
{
	uint32_t rlc_pg_cntl;

	rlc_pg_cntl = RREG32_SOC15(GC, 0, mmRLC_PG_CNTL);

	if (!enable) {
		/* RLC_PG_CNTL[23] = 0 (default)
		 * RLC will wait for handshake acks with SMU
		 * GFXOFF will be enabled
		 * RLC_PG_CNTL[23] = 1
		 * RLC will not issue any message to SMU
		 * hence no handshake between SMU & RLC
		 * GFXOFF will be disabled
		 */
		rlc_pg_cntl |= 0x800000;
	} else
		rlc_pg_cntl &= ~0x800000;
	WREG32_SOC15(GC, 0, mmRLC_PG_CNTL, rlc_pg_cntl);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int save_restore_gpu_addr; int clear_state_gpu_addr; } ;
struct radeon_device {TYPE_1__ rlc; } ;

/* Variables and functions */
 int GFX_PG_SRC ; 
 int GRBM_REG_SGIT (int) ; 
 int GRBM_REG_SGIT_MASK ; 
 int PG_AFTER_GRBM_REG_ST_MASK ; 
 int /*<<< orphan*/  RLC_AUTO_PG_CTRL ; 
 int /*<<< orphan*/  RLC_CLEAR_STATE_RESTORE_BASE ; 
 int /*<<< orphan*/  RLC_PG_CNTL ; 
 int /*<<< orphan*/  RLC_SAVE_AND_RESTORE_BASE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_init_gfx_cgpg(struct radeon_device *rdev)
{
	u32 tmp;

	WREG32(RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);

	tmp = RREG32(RLC_PG_CNTL);
	tmp |= GFX_PG_SRC;
	WREG32(RLC_PG_CNTL, tmp);

	WREG32(RLC_CLEAR_STATE_RESTORE_BASE, rdev->rlc.clear_state_gpu_addr >> 8);

	tmp = RREG32(RLC_AUTO_PG_CTRL);

	tmp &= ~GRBM_REG_SGIT_MASK;
	tmp |= GRBM_REG_SGIT(0x700);
	tmp &= ~PG_AFTER_GRBM_REG_ST_MASK;
	WREG32(RLC_AUTO_PG_CTRL, tmp);
}
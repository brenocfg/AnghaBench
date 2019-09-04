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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_BUSY_INT_ENABLE ; 
 int /*<<< orphan*/  CNTX_BUSY_INT_ENABLE ; 
 int /*<<< orphan*/  CNTX_EMPTY_INT_ENABLE ; 
 int /*<<< orphan*/  CP_INT_CNTL_RING0 ; 
 int /*<<< orphan*/  GFX_IDLE_INT_ENABLE ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_INT_CNTL_RING0 ; 

__attribute__((used)) static void gfx_v8_0_enable_gui_idle_interrupt(struct amdgpu_device *adev,
					       bool enable)
{
	u32 tmp = RREG32(mmCP_INT_CNTL_RING0);

	tmp = REG_SET_FIELD(tmp, CP_INT_CNTL_RING0, CNTX_BUSY_INT_ENABLE, enable ? 1 : 0);
	tmp = REG_SET_FIELD(tmp, CP_INT_CNTL_RING0, CNTX_EMPTY_INT_ENABLE, enable ? 1 : 0);
	tmp = REG_SET_FIELD(tmp, CP_INT_CNTL_RING0, CMP_BUSY_INT_ENABLE, enable ? 1 : 0);
	tmp = REG_SET_FIELD(tmp, CP_INT_CNTL_RING0, GFX_IDLE_INT_ENABLE, enable ? 1 : 0);

	WREG32(mmCP_INT_CNTL_RING0, tmp);
}
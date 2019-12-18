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
 int SRBM_GFX_CNTL__MEID_MASK ; 
 int SRBM_GFX_CNTL__MEID__SHIFT ; 
 int SRBM_GFX_CNTL__PIPEID_MASK ; 
 int SRBM_GFX_CNTL__PIPEID__SHIFT ; 
 int SRBM_GFX_CNTL__QUEUEID_MASK ; 
 int SRBM_GFX_CNTL__QUEUEID__SHIFT ; 
 int SRBM_GFX_CNTL__VMID_MASK ; 
 int SRBM_GFX_CNTL__VMID__SHIFT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmSRBM_GFX_CNTL ; 

void cik_srbm_select(struct amdgpu_device *adev,
		     u32 me, u32 pipe, u32 queue, u32 vmid)
{
	u32 srbm_gfx_cntl =
		(((pipe << SRBM_GFX_CNTL__PIPEID__SHIFT) & SRBM_GFX_CNTL__PIPEID_MASK)|
		((me << SRBM_GFX_CNTL__MEID__SHIFT) & SRBM_GFX_CNTL__MEID_MASK)|
		((vmid << SRBM_GFX_CNTL__VMID__SHIFT) & SRBM_GFX_CNTL__VMID_MASK)|
		((queue << SRBM_GFX_CNTL__QUEUEID__SHIFT) & SRBM_GFX_CNTL__QUEUEID_MASK));
	WREG32(mmSRBM_GFX_CNTL, srbm_gfx_cntl);
}
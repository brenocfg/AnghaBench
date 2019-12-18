#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct kgd_dev {int dummy; } ;
struct TYPE_3__ {int num_pipe_per_mec; } ;
struct TYPE_4__ {TYPE_1__ mec; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int CP_INT_CNTL_RING0__OPCODE_ERROR_INT_ENABLE_MASK ; 
 int CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  lock_srbm (struct kgd_dev*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCPC_INT_CNTL ; 
 int /*<<< orphan*/  unlock_srbm (struct kgd_dev*) ; 

int kgd_gfx_v9_init_interrupts(struct kgd_dev *kgd, uint32_t pipe_id)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	uint32_t mec;
	uint32_t pipe;

	mec = (pipe_id / adev->gfx.mec.num_pipe_per_mec) + 1;
	pipe = (pipe_id % adev->gfx.mec.num_pipe_per_mec);

	lock_srbm(kgd, mec, pipe, 0, 0);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmCPC_INT_CNTL),
		CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK |
		CP_INT_CNTL_RING0__OPCODE_ERROR_INT_ENABLE_MASK);

	unlock_srbm(kgd);

	return 0;
}
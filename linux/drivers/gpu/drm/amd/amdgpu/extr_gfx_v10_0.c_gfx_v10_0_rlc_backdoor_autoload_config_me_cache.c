#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ rlc_autoload_gpu_addr; } ;
struct TYPE_5__ {TYPE_1__ rlc; } ;
struct amdgpu_device {TYPE_2__ gfx; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ME_IC_OP_CNTL ; 
 int EINVAL ; 
 size_t FIRMWARE_ID_CP_ME ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  INVALIDATE_CACHE ; 
 int /*<<< orphan*/  INVALIDATE_CACHE_COMPLETE ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mmCP_ME_IC_BASE_HI ; 
 int /*<<< orphan*/  mmCP_ME_IC_BASE_LO ; 
 int /*<<< orphan*/  mmCP_ME_IC_OP_CNTL ; 
 TYPE_3__* rlc_autoload_info ; 
 int /*<<< orphan*/  udelay (int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int gfx_v10_0_rlc_backdoor_autoload_config_me_cache(struct amdgpu_device *adev)
{
	uint32_t usec_timeout = 50000;  /* wait for 50ms */
	uint32_t tmp;
	int i;
	uint64_t addr;

	/* Trigger an invalidation of the L1 instruction caches */
	tmp = RREG32_SOC15(GC, 0, mmCP_ME_IC_OP_CNTL);
	tmp = REG_SET_FIELD(tmp, CP_ME_IC_OP_CNTL, INVALIDATE_CACHE, 1);
	WREG32_SOC15(GC, 0, mmCP_ME_IC_OP_CNTL, tmp);

	/* Wait for invalidation complete */
	for (i = 0; i < usec_timeout; i++) {
		tmp = RREG32_SOC15(GC, 0, mmCP_ME_IC_OP_CNTL);
		if (1 == REG_GET_FIELD(tmp, CP_ME_IC_OP_CNTL,
			INVALIDATE_CACHE_COMPLETE))
			break;
		udelay(1);
	}

	if (i >= usec_timeout) {
		dev_err(adev->dev, "failed to invalidate instruction cache\n");
		return -EINVAL;
	}

	/* Program me ucode address into intruction cache address register */
	addr = adev->gfx.rlc.rlc_autoload_gpu_addr +
		rlc_autoload_info[FIRMWARE_ID_CP_ME].offset;
	WREG32_SOC15(GC, 0, mmCP_ME_IC_BASE_LO,
			lower_32_bits(addr) & 0xFFFFF000);
	WREG32_SOC15(GC, 0, mmCP_ME_IC_BASE_HI,
			upper_32_bits(addr));

	return 0;
}
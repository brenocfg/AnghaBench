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
struct psp_context {int /*<<< orphan*/  tmr_buf; int /*<<< orphan*/  tmr_mc_addr; int /*<<< orphan*/  tmr_bo; int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int amdgpu_bo_create_kernel (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psp_tmr_init(struct psp_context *psp)
{
	int ret;

	/*
	 * Allocate 3M memory aligned to 1M from Frame Buffer (local
	 * physical).
	 *
	 * Note: this memory need be reserved till the driver
	 * uninitializes.
	 */
	ret = amdgpu_bo_create_kernel(psp->adev, 0x300000, 0x100000,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->tmr_bo, &psp->tmr_mc_addr, &psp->tmr_buf);

	return ret;
}
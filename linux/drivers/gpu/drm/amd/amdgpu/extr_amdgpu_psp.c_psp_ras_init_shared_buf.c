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
struct TYPE_2__ {int /*<<< orphan*/  ras_shared_buf; int /*<<< orphan*/  ras_shared_mc_addr; int /*<<< orphan*/  ras_shared_bo; } ;
struct psp_context {TYPE_1__ ras; int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PSP_RAS_SHARED_MEM_SIZE ; 
 int amdgpu_bo_create_kernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psp_ras_init_shared_buf(struct psp_context *psp)
{
	int ret;

	/*
	 * Allocate 16k memory aligned to 4k from Frame Buffer (local
	 * physical) for ras ta <-> Driver
	 */
	ret = amdgpu_bo_create_kernel(psp->adev, PSP_RAS_SHARED_MEM_SIZE,
			PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
			&psp->ras.ras_shared_bo,
			&psp->ras.ras_shared_mc_addr,
			&psp->ras.ras_shared_buf);

	return ret;
}
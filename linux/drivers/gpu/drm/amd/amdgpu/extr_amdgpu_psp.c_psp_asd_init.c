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
struct psp_context {int /*<<< orphan*/  asd_shared_buf; int /*<<< orphan*/  asd_shared_mc_addr; int /*<<< orphan*/  asd_shared_bo; int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PSP_ASD_SHARED_MEM_SIZE ; 
 int amdgpu_bo_create_kernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psp_asd_init(struct psp_context *psp)
{
	int ret;

	/*
	 * Allocate 16k memory aligned to 4k from Frame Buffer (local
	 * physical) for shared ASD <-> Driver
	 */
	ret = amdgpu_bo_create_kernel(psp->adev, PSP_ASD_SHARED_MEM_SIZE,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->asd_shared_bo,
				      &psp->asd_shared_mc_addr,
				      &psp->asd_shared_buf);

	return ret;
}
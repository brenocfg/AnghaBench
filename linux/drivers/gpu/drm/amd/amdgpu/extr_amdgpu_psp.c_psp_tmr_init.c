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
struct psp_context {int /*<<< orphan*/  tmr_mc_addr; int /*<<< orphan*/  tmr_bo; int /*<<< orphan*/  adev; scalar_t__ fw_pri_buf; scalar_t__ toc_bin_size; scalar_t__ toc_start_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int PSP_TMR_SIZE ; 
 int amdgpu_bo_create_kernel (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ amdgpu_sriov_vf (int /*<<< orphan*/ ) ; 
 int psp_load_toc (struct psp_context*,int*) ; 

__attribute__((used)) static int psp_tmr_init(struct psp_context *psp)
{
	int ret;
	int tmr_size;
	void *tmr_buf;
	void **pptr;

	/*
	 * According to HW engineer, they prefer the TMR address be "naturally
	 * aligned" , e.g. the start address be an integer divide of TMR size.
	 *
	 * Note: this memory need be reserved till the driver
	 * uninitializes.
	 */
	tmr_size = PSP_TMR_SIZE;

	/* For ASICs support RLC autoload, psp will parse the toc
	 * and calculate the total size of TMR needed */
	if (psp->toc_start_addr &&
	    psp->toc_bin_size &&
	    psp->fw_pri_buf) {
		ret = psp_load_toc(psp, &tmr_size);
		if (ret) {
			DRM_ERROR("Failed to load toc\n");
			return ret;
		}
	}

	pptr = amdgpu_sriov_vf(psp->adev) ? &tmr_buf : NULL;
	ret = amdgpu_bo_create_kernel(psp->adev, tmr_size, PSP_TMR_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &psp->tmr_bo, &psp->tmr_mc_addr, pptr);

	return ret;
}
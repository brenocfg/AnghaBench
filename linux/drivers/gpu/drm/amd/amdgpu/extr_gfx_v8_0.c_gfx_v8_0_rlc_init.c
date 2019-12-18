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
struct cs_section_def {int dummy; } ;
struct TYPE_3__ {scalar_t__ cp_table_size; struct cs_section_def* cs_data; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_2__ gfx; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int) ; 
 scalar_t__ CHIP_CARRIZO ; 
 scalar_t__ CHIP_STONEY ; 
 int amdgpu_gfx_rlc_init_cpt (struct amdgpu_device*) ; 
 int amdgpu_gfx_rlc_init_csb (struct amdgpu_device*) ; 
 struct cs_section_def* vi_cs_data ; 

__attribute__((used)) static int gfx_v8_0_rlc_init(struct amdgpu_device *adev)
{
	const struct cs_section_def *cs_data;
	int r;

	adev->gfx.rlc.cs_data = vi_cs_data;

	cs_data = adev->gfx.rlc.cs_data;

	if (cs_data) {
		/* init clear state block */
		r = amdgpu_gfx_rlc_init_csb(adev);
		if (r)
			return r;
	}

	if ((adev->asic_type == CHIP_CARRIZO) ||
	    (adev->asic_type == CHIP_STONEY)) {
		adev->gfx.rlc.cp_table_size = ALIGN(96 * 5 * 4, 2048) + (64 * 1024); /* JT + GDS */
		r = amdgpu_gfx_rlc_init_cpt(adev);
		if (r)
			return r;
	}

	return 0;
}
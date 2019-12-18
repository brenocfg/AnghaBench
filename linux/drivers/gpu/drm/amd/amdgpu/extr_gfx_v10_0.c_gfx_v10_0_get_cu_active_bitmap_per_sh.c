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
 int gfx_v10_0_get_wgp_active_bitmap_per_sh (struct amdgpu_device*) ; 

__attribute__((used)) static u32 gfx_v10_0_get_cu_active_bitmap_per_sh(struct amdgpu_device *adev)
{
	u32 wgp_idx, wgp_active_bitmap;
	u32 cu_bitmap_per_wgp, cu_active_bitmap;

	wgp_active_bitmap = gfx_v10_0_get_wgp_active_bitmap_per_sh(adev);
	cu_active_bitmap = 0;

	for (wgp_idx = 0; wgp_idx < 16; wgp_idx++) {
		/* if there is one WGP enabled, it means 2 CUs will be enabled */
		cu_bitmap_per_wgp = 3 << (2 * wgp_idx);
		if (wgp_active_bitmap & (1 << wgp_idx))
			cu_active_bitmap |= cu_bitmap_per_wgp;
	}

	return cu_active_bitmap;
}
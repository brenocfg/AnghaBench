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
struct intel_vgpu_page_track {int tracked; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int intel_gvt_hypervisor_enable_page_track (struct intel_vgpu*,unsigned long) ; 
 struct intel_vgpu_page_track* intel_vgpu_find_page_track (struct intel_vgpu*,unsigned long) ; 

int intel_vgpu_enable_page_track(struct intel_vgpu *vgpu, unsigned long gfn)
{
	struct intel_vgpu_page_track *track;
	int ret;

	track = intel_vgpu_find_page_track(vgpu, gfn);
	if (!track)
		return -ENXIO;

	if (track->tracked)
		return 0;

	ret = intel_gvt_hypervisor_enable_page_track(vgpu, gfn);
	if (ret)
		return ret;
	track->tracked = true;
	return 0;
}
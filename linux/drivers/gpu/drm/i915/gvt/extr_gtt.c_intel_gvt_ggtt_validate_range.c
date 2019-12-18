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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gvt_dbg_mm (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ vgpu_gmadr_is_aperture (struct intel_vgpu*,scalar_t__) ; 
 scalar_t__ vgpu_gmadr_is_hidden (struct intel_vgpu*,scalar_t__) ; 
 int vgpu_gmadr_is_valid (struct intel_vgpu*,scalar_t__) ; 

bool intel_gvt_ggtt_validate_range(struct intel_vgpu *vgpu, u64 addr, u32 size)
{
	if (size == 0)
		return vgpu_gmadr_is_valid(vgpu, addr);

	if (vgpu_gmadr_is_aperture(vgpu, addr) &&
	    vgpu_gmadr_is_aperture(vgpu, addr + size - 1))
		return true;
	else if (vgpu_gmadr_is_hidden(vgpu, addr) &&
		 vgpu_gmadr_is_hidden(vgpu, addr + size - 1))
		return true;

	gvt_dbg_mm("Invalid ggtt range at 0x%llx, size: 0x%x\n",
		     addr, size);
	return false;
}
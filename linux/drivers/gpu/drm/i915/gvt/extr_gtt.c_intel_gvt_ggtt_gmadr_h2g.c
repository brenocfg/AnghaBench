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
struct intel_vgpu {int /*<<< orphan*/  gvt; } ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ WARN (int,char*,scalar_t__) ; 
 scalar_t__ gvt_aperture_gmadr_base (int /*<<< orphan*/ ) ; 
 scalar_t__ gvt_gmadr_is_aperture (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gvt_gmadr_is_valid (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gvt_hidden_gmadr_base (int /*<<< orphan*/ ) ; 
 scalar_t__ vgpu_aperture_gmadr_base (struct intel_vgpu*) ; 
 scalar_t__ vgpu_hidden_gmadr_base (struct intel_vgpu*) ; 

int intel_gvt_ggtt_gmadr_h2g(struct intel_vgpu *vgpu, u64 h_addr, u64 *g_addr)
{
	if (WARN(!gvt_gmadr_is_valid(vgpu->gvt, h_addr),
		 "invalid host gmadr %llx\n", h_addr))
		return -EACCES;

	if (gvt_gmadr_is_aperture(vgpu->gvt, h_addr))
		*g_addr = vgpu_aperture_gmadr_base(vgpu)
			+ (h_addr - gvt_aperture_gmadr_base(vgpu->gvt));
	else
		*g_addr = vgpu_hidden_gmadr_base(vgpu)
			+ (h_addr - gvt_hidden_gmadr_base(vgpu->gvt));
	return 0;
}
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
typedef  unsigned long u64 ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 unsigned long I915_GTT_PAGE_SHIFT ; 
 int intel_gvt_ggtt_gmadr_h2g (struct intel_vgpu*,unsigned long,unsigned long*) ; 

int intel_gvt_ggtt_h2g_index(struct intel_vgpu *vgpu, unsigned long h_index,
			     unsigned long *g_index)
{
	u64 g_addr;
	int ret;

	ret = intel_gvt_ggtt_gmadr_h2g(vgpu, h_index << I915_GTT_PAGE_SHIFT,
				       &g_addr);
	if (ret)
		return ret;

	*g_index = g_addr >> I915_GTT_PAGE_SHIFT;
	return 0;
}
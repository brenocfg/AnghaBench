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
struct intel_vgpu {int /*<<< orphan*/  pv_notified; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GVT_FAILSAFE_UNSUPPORTED_GUEST ; 
 int /*<<< orphan*/  enter_failsafe_mode (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int vgpu_fence_sz (struct intel_vgpu*) ; 

__attribute__((used)) static int sanitize_fence_mmio_access(struct intel_vgpu *vgpu,
		unsigned int fence_num, void *p_data, unsigned int bytes)
{
	unsigned int max_fence = vgpu_fence_sz(vgpu);

	if (fence_num >= max_fence) {
		gvt_vgpu_err("access oob fence reg %d/%d\n",
			     fence_num, max_fence);

		/* When guest access oob fence regs without access
		 * pv_info first, we treat guest not supporting GVT,
		 * and we will let vgpu enter failsafe mode.
		 */
		if (!vgpu->pv_notified)
			enter_failsafe_mode(vgpu,
					GVT_FAILSAFE_UNSUPPORTED_GUEST);

		memset(p_data, 0, bytes);
		return -EINVAL;
	}
	return 0;
}
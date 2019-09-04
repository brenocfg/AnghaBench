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
typedef  int /*<<< orphan*/  u64 ;
struct intel_vgpu_mm {int dummy; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 struct intel_vgpu_mm* intel_vgpu_find_ppgtt_mm (struct intel_vgpu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_vgpu_mm_put (struct intel_vgpu_mm*) ; 

int intel_vgpu_put_ppgtt_mm(struct intel_vgpu *vgpu, u64 pdps[])
{
	struct intel_vgpu_mm *mm;

	mm = intel_vgpu_find_ppgtt_mm(vgpu, pdps);
	if (!mm) {
		gvt_vgpu_err("fail to find ppgtt instance.\n");
		return -EINVAL;
	}
	intel_vgpu_mm_put(mm);
	return 0;
}
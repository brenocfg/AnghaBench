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
struct intel_vgpu_workload {struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 int scan_workload (struct intel_vgpu_workload*) ; 
 int shadow_workload_ring_buffer (struct intel_vgpu_workload*) ; 

int intel_gvt_scan_and_shadow_ringbuffer(struct intel_vgpu_workload *workload)
{
	int ret;
	struct intel_vgpu *vgpu = workload->vgpu;

	ret = shadow_workload_ring_buffer(workload);
	if (ret) {
		gvt_vgpu_err("fail to shadow workload ring_buffer\n");
		return ret;
	}

	ret = scan_workload(workload);
	if (ret) {
		gvt_vgpu_err("scan workload error\n");
		return ret;
	}
	return 0;
}
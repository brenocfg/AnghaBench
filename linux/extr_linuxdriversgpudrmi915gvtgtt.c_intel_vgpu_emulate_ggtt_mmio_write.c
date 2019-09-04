#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_vgpu {TYPE_1__* gvt; } ;
struct intel_gvt_device_info {scalar_t__ gtt_start_offset; } ;
struct TYPE_2__ {struct intel_gvt_device_info device_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int emulate_ggtt_mmio_write (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

int intel_vgpu_emulate_ggtt_mmio_write(struct intel_vgpu *vgpu,
		unsigned int off, void *p_data, unsigned int bytes)
{
	const struct intel_gvt_device_info *info = &vgpu->gvt->device_info;
	int ret;

	if (bytes != 4 && bytes != 8)
		return -EINVAL;

	off -= info->gtt_start_offset;
	ret = emulate_ggtt_mmio_write(vgpu, off, p_data, bytes);
	return ret;
}
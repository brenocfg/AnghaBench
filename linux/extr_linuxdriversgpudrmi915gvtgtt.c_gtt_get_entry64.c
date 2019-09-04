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
typedef  int /*<<< orphan*/  u64 ;
struct intel_vgpu {TYPE_1__* gvt; } ;
struct intel_gvt_gtt_entry {int /*<<< orphan*/  val64; } ;
struct intel_gvt_device_info {int gtt_entry_size; unsigned long gtt_entry_size_shift; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_priv; struct intel_gvt_device_info device_info; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int intel_gvt_hypervisor_read_gpa (struct intel_vgpu*,unsigned long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_pte64 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline int gtt_get_entry64(void *pt,
		struct intel_gvt_gtt_entry *e,
		unsigned long index, bool hypervisor_access, unsigned long gpa,
		struct intel_vgpu *vgpu)
{
	const struct intel_gvt_device_info *info = &vgpu->gvt->device_info;
	int ret;

	if (WARN_ON(info->gtt_entry_size != 8))
		return -EINVAL;

	if (hypervisor_access) {
		ret = intel_gvt_hypervisor_read_gpa(vgpu, gpa +
				(index << info->gtt_entry_size_shift),
				&e->val64, 8);
		if (WARN_ON(ret))
			return ret;
	} else if (!pt) {
		e->val64 = read_pte64(vgpu->gvt->dev_priv, index);
	} else {
		e->val64 = *((u64 *)pt + index);
	}
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dc; } ;
struct TYPE_4__ {struct amdgpu_crtc** crtcs; } ;
struct amdgpu_device {TYPE_1__ dm; TYPE_2__ mode_info; } ;
struct amdgpu_crtc {int otg_inst; } ;
typedef  enum irq_type { ____Placeholder_irq_type } irq_type ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
 int AMDGPU_IRQ_STATE_ENABLE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  dc_interrupt_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int dm_irq_state(struct amdgpu_device *adev,
			       struct amdgpu_irq_src *source,
			       unsigned crtc_id,
			       enum amdgpu_interrupt_state state,
			       const enum irq_type dal_irq_type,
			       const char *func)
{
	bool st;
	enum dc_irq_source irq_source;

	struct amdgpu_crtc *acrtc = adev->mode_info.crtcs[crtc_id];

	if (!acrtc) {
		DRM_ERROR(
			"%s: crtc is NULL at id :%d\n",
			func,
			crtc_id);
		return 0;
	}

	if (acrtc->otg_inst == -1)
		return 0;

	irq_source = dal_irq_type + acrtc->otg_inst;

	st = (state == AMDGPU_IRQ_STATE_ENABLE);

	dc_interrupt_set(adev->dm.dc, irq_source, st);
	return 0;
}
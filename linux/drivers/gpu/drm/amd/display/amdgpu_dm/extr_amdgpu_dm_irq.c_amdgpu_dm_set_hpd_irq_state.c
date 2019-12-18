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
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dc; } ;
struct amdgpu_device {TYPE_1__ dm; } ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
 int AMDGPU_IRQ_STATE_ENABLE ; 
 int amdgpu_dm_hpd_to_dal_irq_source (unsigned int) ; 
 int /*<<< orphan*/  dc_interrupt_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int amdgpu_dm_set_hpd_irq_state(struct amdgpu_device *adev,
				       struct amdgpu_irq_src *source,
				       unsigned type,
				       enum amdgpu_interrupt_state state)
{
	enum dc_irq_source src = amdgpu_dm_hpd_to_dal_irq_source(type);
	bool st = (state == AMDGPU_IRQ_STATE_ENABLE);

	dc_interrupt_set(adev->dm.dc, src, st);
	return 0;
}
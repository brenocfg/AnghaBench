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
struct pp_hwmgr {scalar_t__ adev; } ;
struct amdgpu_irq_src {int /*<<< orphan*/ * funcs; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_IRQ_CLIENTID_LEGACY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_CG_TSS_THERMAL_HIGH_TO_LOW ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_CG_TSS_THERMAL_LOW_TO_HIGH ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_GPIO_19 ; 
 int /*<<< orphan*/  amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_irq_src*) ; 
 struct amdgpu_irq_src* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu7_irq_funcs ; 

__attribute__((used)) static int smu7_register_irq_handlers(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_irq_src *source =
		kzalloc(sizeof(struct amdgpu_irq_src), GFP_KERNEL);

	if (!source)
		return -ENOMEM;

	source->funcs = &smu7_irq_funcs;

	amdgpu_irq_add_id((struct amdgpu_device *)(hwmgr->adev),
			AMDGPU_IRQ_CLIENTID_LEGACY,
			VISLANDS30_IV_SRCID_CG_TSS_THERMAL_LOW_TO_HIGH,
			source);
	amdgpu_irq_add_id((struct amdgpu_device *)(hwmgr->adev),
			AMDGPU_IRQ_CLIENTID_LEGACY,
			VISLANDS30_IV_SRCID_CG_TSS_THERMAL_HIGH_TO_LOW,
			source);

	/* Register CTF(GPIO_19) interrupt */
	amdgpu_irq_add_id((struct amdgpu_device *)(hwmgr->adev),
			AMDGPU_IRQ_CLIENTID_LEGACY,
			VISLANDS30_IV_SRCID_GPIO_19,
			source);

	return 0;
}
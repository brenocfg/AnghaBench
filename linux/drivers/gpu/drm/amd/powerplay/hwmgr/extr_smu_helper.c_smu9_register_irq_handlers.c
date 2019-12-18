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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMUIO_9_0__SRCID__SMUIO_GPIO19 ; 
 int /*<<< orphan*/  SOC15_IH_CLIENTID_ROM_SMUIO ; 
 int /*<<< orphan*/  SOC15_IH_CLIENTID_THM ; 
 int /*<<< orphan*/  THM_9_0__SRCID__THM_DIG_THERM_H2L ; 
 int /*<<< orphan*/  THM_9_0__SRCID__THM_DIG_THERM_L2H ; 
 int /*<<< orphan*/  amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_irq_src*) ; 
 struct amdgpu_irq_src* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu9_irq_funcs ; 

int smu9_register_irq_handlers(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_irq_src *source =
		kzalloc(sizeof(struct amdgpu_irq_src), GFP_KERNEL);

	if (!source)
		return -ENOMEM;

	source->funcs = &smu9_irq_funcs;

	amdgpu_irq_add_id((struct amdgpu_device *)(hwmgr->adev),
			SOC15_IH_CLIENTID_THM,
			THM_9_0__SRCID__THM_DIG_THERM_L2H,
			source);
	amdgpu_irq_add_id((struct amdgpu_device *)(hwmgr->adev),
			SOC15_IH_CLIENTID_THM,
			THM_9_0__SRCID__THM_DIG_THERM_H2L,
			source);

	/* Register CTF(GPIO_19) interrupt */
	amdgpu_irq_add_id((struct amdgpu_device *)(hwmgr->adev),
			SOC15_IH_CLIENTID_ROM_SMUIO,
			SMUIO_9_0__SRCID__SMUIO_GPIO19,
			source);

	return 0;
}
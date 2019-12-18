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
struct smu_context {struct amdgpu_irq_src* irq_source; struct amdgpu_device* adev; } ;
struct amdgpu_irq_src {int /*<<< orphan*/ * funcs; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SOC15_IH_CLIENTID_THM ; 
 int /*<<< orphan*/  THM_11_0__SRCID__THM_DIG_THERM_H2L ; 
 int /*<<< orphan*/  THM_11_0__SRCID__THM_DIG_THERM_L2H ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_irq_src*) ; 
 struct amdgpu_irq_src* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_v11_0_irq_funcs ; 

__attribute__((used)) static int smu_v11_0_register_irq_handler(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	struct amdgpu_irq_src *irq_src = smu->irq_source;
	int ret = 0;

	/* already register */
	if (irq_src)
		return 0;

	irq_src = kzalloc(sizeof(struct amdgpu_irq_src), GFP_KERNEL);
	if (!irq_src)
		return -ENOMEM;
	smu->irq_source = irq_src;

	irq_src->funcs = &smu_v11_0_irq_funcs;

	ret = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_THM,
				THM_11_0__SRCID__THM_DIG_THERM_L2H,
				irq_src);
	if (ret)
		return ret;

	ret = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_THM,
				THM_11_0__SRCID__THM_DIG_THERM_H2L,
				irq_src);
	if (ret)
		return ret;

	return ret;
}
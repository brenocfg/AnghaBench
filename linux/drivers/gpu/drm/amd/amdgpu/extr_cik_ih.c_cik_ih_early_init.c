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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int amdgpu_irq_add_domain (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cik_ih_set_interrupt_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int cik_ih_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int ret;

	ret = amdgpu_irq_add_domain(adev);
	if (ret)
		return ret;

	cik_ih_set_interrupt_funcs(adev);

	return 0;
}
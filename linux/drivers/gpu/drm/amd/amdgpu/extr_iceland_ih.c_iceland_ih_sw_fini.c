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
struct TYPE_2__ {int /*<<< orphan*/  ih; } ;
struct amdgpu_device {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ih_ring_fini (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_irq_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_irq_remove_domain (struct amdgpu_device*) ; 

__attribute__((used)) static int iceland_ih_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	amdgpu_irq_fini(adev);
	amdgpu_ih_ring_fini(adev, &adev->irq.ih);
	amdgpu_irq_remove_domain(adev);

	return 0;
}
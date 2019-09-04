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
struct TYPE_3__ {int /*<<< orphan*/ * faults; } ;
struct TYPE_4__ {TYPE_1__ ih; } ;
struct amdgpu_device {TYPE_2__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ih_ring_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_irq_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vega10_ih_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	amdgpu_irq_fini(adev);
	amdgpu_ih_ring_fini(adev);

	kfree(adev->irq.ih.faults);
	adev->irq.ih.faults = NULL;

	return 0;
}
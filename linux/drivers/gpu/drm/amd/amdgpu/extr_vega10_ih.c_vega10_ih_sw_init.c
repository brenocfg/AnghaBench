#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ih; } ;
struct TYPE_6__ {int use_doorbell; int doorbell_index; } ;
struct TYPE_4__ {TYPE_3__ ih2; TYPE_3__ ih1; TYPE_3__ ih; int /*<<< orphan*/  self_irq; } ;
struct amdgpu_device {TYPE_2__ doorbell_index; TYPE_1__ irq; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SOC15_IH_CLIENTID_IH ; 
 int amdgpu_ih_ring_init (struct amdgpu_device*,TYPE_3__*,int,int) ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int amdgpu_irq_init (struct amdgpu_device*) ; 

__attribute__((used)) static int vega10_ih_sw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int r;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_IH, 0,
			      &adev->irq.self_irq);
	if (r)
		return r;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih, 256 * 1024, true);
	if (r)
		return r;

	adev->irq.ih.use_doorbell = true;
	adev->irq.ih.doorbell_index = adev->doorbell_index.ih << 1;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih1, PAGE_SIZE, true);
	if (r)
		return r;

	adev->irq.ih1.use_doorbell = true;
	adev->irq.ih1.doorbell_index = (adev->doorbell_index.ih + 1) << 1;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih2, PAGE_SIZE, true);
	if (r)
		return r;

	adev->irq.ih2.use_doorbell = true;
	adev->irq.ih2.doorbell_index = (adev->doorbell_index.ih + 2) << 1;

	r = amdgpu_irq_init(adev);

	return r;
}
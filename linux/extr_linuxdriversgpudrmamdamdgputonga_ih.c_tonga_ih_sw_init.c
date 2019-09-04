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
struct TYPE_3__ {int use_doorbell; int /*<<< orphan*/  doorbell_index; } ;
struct TYPE_4__ {TYPE_1__ ih; } ;
struct amdgpu_device {TYPE_2__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_DOORBELL_IH ; 
 int amdgpu_ih_ring_init (struct amdgpu_device*,int,int) ; 
 int amdgpu_irq_init (struct amdgpu_device*) ; 

__attribute__((used)) static int tonga_ih_sw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	r = amdgpu_ih_ring_init(adev, 64 * 1024, true);
	if (r)
		return r;

	adev->irq.ih.use_doorbell = true;
	adev->irq.ih.doorbell_index = AMDGPU_DOORBELL_IH;

	r = amdgpu_irq_init(adev);

	return r;
}
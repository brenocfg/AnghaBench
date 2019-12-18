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
struct TYPE_4__ {int /*<<< orphan*/  ih; } ;
struct TYPE_6__ {int use_doorbell; int /*<<< orphan*/  doorbell_index; } ;
struct TYPE_5__ {TYPE_3__ ih; } ;
struct amdgpu_device {TYPE_1__ doorbell_index; TYPE_2__ irq; } ;

/* Variables and functions */
 int amdgpu_ih_ring_init (struct amdgpu_device*,TYPE_3__*,int,int) ; 
 int amdgpu_irq_init (struct amdgpu_device*) ; 

__attribute__((used)) static int tonga_ih_sw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih, 64 * 1024, true);
	if (r)
		return r;

	adev->irq.ih.use_doorbell = true;
	adev->irq.ih.doorbell_index = adev->doorbell_index.ih;

	r = amdgpu_irq_init(adev);

	return r;
}
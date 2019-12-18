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
struct amdgpu_ring {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_IRQ_CLIENTID_LEGACY ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int amdgpu_uvd_entity_init (struct amdgpu_device*) ; 
 int amdgpu_uvd_resume (struct amdgpu_device*) ; 
 int amdgpu_uvd_sw_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int uvd_v4_2_sw_init(void *handle)
{
	struct amdgpu_ring *ring;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int r;

	/* UVD TRAP */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 124, &adev->uvd.inst->irq);
	if (r)
		return r;

	r = amdgpu_uvd_sw_init(adev);
	if (r)
		return r;

	ring = &adev->uvd.inst->ring;
	sprintf(ring->name, "uvd");
	r = amdgpu_ring_init(adev, ring, 512, &adev->uvd.inst->irq, 0);
	if (r)
		return r;

	r = amdgpu_uvd_resume(adev);
	if (r)
		return r;

	r = amdgpu_uvd_entity_init(adev);

	return r;
}
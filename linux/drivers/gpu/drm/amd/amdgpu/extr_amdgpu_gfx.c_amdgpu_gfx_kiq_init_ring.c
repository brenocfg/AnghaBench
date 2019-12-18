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
struct amdgpu_ring {int use_doorbell; int me; int pipe; int queue; int /*<<< orphan*/  name; int /*<<< orphan*/  eop_gpu_addr; int /*<<< orphan*/  doorbell_index; int /*<<< orphan*/ * ring_obj; int /*<<< orphan*/ * adev; } ;
struct amdgpu_kiq {int /*<<< orphan*/  eop_gpu_addr; int /*<<< orphan*/  ring_lock; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  kiq; } ;
struct TYPE_5__ {int /*<<< orphan*/  reg_val_offs; } ;
struct TYPE_4__ {struct amdgpu_kiq kiq; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_3__ doorbell_index; TYPE_2__ virt; TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CP_KIQ_IRQ_DRIVER0 ; 
 int amdgpu_device_wb_get (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int amdgpu_gfx_kiq_acquire (struct amdgpu_device*,struct amdgpu_ring*) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,struct amdgpu_irq_src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 

int amdgpu_gfx_kiq_init_ring(struct amdgpu_device *adev,
			     struct amdgpu_ring *ring,
			     struct amdgpu_irq_src *irq)
{
	struct amdgpu_kiq *kiq = &adev->gfx.kiq;
	int r = 0;

	spin_lock_init(&kiq->ring_lock);

	r = amdgpu_device_wb_get(adev, &adev->virt.reg_val_offs);
	if (r)
		return r;

	ring->adev = NULL;
	ring->ring_obj = NULL;
	ring->use_doorbell = true;
	ring->doorbell_index = adev->doorbell_index.kiq;

	r = amdgpu_gfx_kiq_acquire(adev, ring);
	if (r)
		return r;

	ring->eop_gpu_addr = kiq->eop_gpu_addr;
	sprintf(ring->name, "kiq_%d.%d.%d", ring->me, ring->pipe, ring->queue);
	r = amdgpu_ring_init(adev, ring, 1024,
			     irq, AMDGPU_CP_KIQ_IRQ_DRIVER0);
	if (r)
		dev_warn(adev->dev, "(%d) failed to init kiq ring\n", r);

	return r;
}
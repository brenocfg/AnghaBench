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
struct amdgpu_ring {int me; int pipe; int queue; int use_doorbell; int doorbell_index; int /*<<< orphan*/  name; int /*<<< orphan*/ * ring_obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  eop_irq; struct amdgpu_ring* gfx_ring; } ;
struct TYPE_3__ {int gfx_ring0; int gfx_ring1; } ;
struct amdgpu_device {TYPE_2__ gfx; TYPE_1__ doorbell_index; } ;

/* Variables and functions */
 unsigned int AMDGPU_CP_IRQ_GFX_ME0_PIPE0_EOP ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static int gfx_v10_0_gfx_ring_init(struct amdgpu_device *adev, int ring_id,
				   int me, int pipe, int queue)
{
	int r;
	struct amdgpu_ring *ring;
	unsigned int irq_type;

	ring = &adev->gfx.gfx_ring[ring_id];

	ring->me = me;
	ring->pipe = pipe;
	ring->queue = queue;

	ring->ring_obj = NULL;
	ring->use_doorbell = true;

	if (!ring_id)
		ring->doorbell_index = adev->doorbell_index.gfx_ring0 << 1;
	else
		ring->doorbell_index = adev->doorbell_index.gfx_ring1 << 1;
	sprintf(ring->name, "gfx_%d.%d.%d", ring->me, ring->pipe, ring->queue);

	irq_type = AMDGPU_CP_IRQ_GFX_ME0_PIPE0_EOP + ring->pipe;
	r = amdgpu_ring_init(adev, ring, 1024,
			     &adev->gfx.eop_irq, irq_type);
	if (r)
		return r;
	return 0;
}
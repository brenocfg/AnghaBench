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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u32 ;
struct amdgpu_iv_entry {unsigned int client_id; unsigned int src_id; int /*<<< orphan*/  const* iv_entry; } ;
struct amdgpu_irq_src {TYPE_3__* funcs; } ;
struct amdgpu_ih_ring {int rptr; int /*<<< orphan*/ * ring; } ;
struct TYPE_5__ {TYPE_1__* client; int /*<<< orphan*/  domain; scalar_t__* virq; struct amdgpu_ih_ring ih; } ;
struct amdgpu_device {TYPE_2__ irq; } ;
struct TYPE_6__ {int (* process ) (struct amdgpu_device*,struct amdgpu_irq_src*,struct amdgpu_iv_entry*) ;} ;
struct TYPE_4__ {struct amdgpu_irq_src** sources; } ;

/* Variables and functions */
 unsigned int AMDGPU_IRQ_CLIENTID_MAX ; 
 unsigned int AMDGPU_MAX_IRQ_SRC_ID ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_interrupt (struct amdgpu_device*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  amdgpu_ih_decode_iv (struct amdgpu_device*,struct amdgpu_iv_entry*) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct amdgpu_device*,struct amdgpu_irq_src*,struct amdgpu_iv_entry*) ; 
 int /*<<< orphan*/  trace_amdgpu_iv (int,struct amdgpu_iv_entry*) ; 

void amdgpu_irq_dispatch(struct amdgpu_device *adev,
			 struct amdgpu_ih_ring *ih)
{
	u32 ring_index = ih->rptr >> 2;
	struct amdgpu_iv_entry entry;
	unsigned client_id, src_id;
	struct amdgpu_irq_src *src;
	bool handled = false;
	int r;

	entry.iv_entry = (const uint32_t *)&ih->ring[ring_index];
	amdgpu_ih_decode_iv(adev, &entry);

	trace_amdgpu_iv(ih - &adev->irq.ih, &entry);

	client_id = entry.client_id;
	src_id = entry.src_id;

	if (client_id >= AMDGPU_IRQ_CLIENTID_MAX) {
		DRM_DEBUG("Invalid client_id in IV: %d\n", client_id);

	} else	if (src_id >= AMDGPU_MAX_IRQ_SRC_ID) {
		DRM_DEBUG("Invalid src_id in IV: %d\n", src_id);

	} else if (adev->irq.virq[src_id]) {
		generic_handle_irq(irq_find_mapping(adev->irq.domain, src_id));

	} else if (!adev->irq.client[client_id].sources) {
		DRM_DEBUG("Unregistered interrupt client_id: %d src_id: %d\n",
			  client_id, src_id);

	} else if ((src = adev->irq.client[client_id].sources[src_id])) {
		r = src->funcs->process(adev, src, &entry);
		if (r < 0)
			DRM_ERROR("error processing interrupt (%d)\n", r);
		else if (r)
			handled = true;

	} else {
		DRM_DEBUG("Unhandled interrupt src_id: %d\n", src_id);
	}

	/* Send it to amdkfd as well if it isn't already handled */
	if (!handled)
		amdgpu_amdkfd_interrupt(adev, entry.iv_entry);
}
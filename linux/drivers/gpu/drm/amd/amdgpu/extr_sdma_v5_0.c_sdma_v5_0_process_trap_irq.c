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
struct amdgpu_iv_entry {int client_id; int /*<<< orphan*/  ring_id; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_3__ {TYPE_2__* instance; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;
struct TYPE_4__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
#define  SOC15_IH_CLIENTID_SDMA0 129 
#define  SOC15_IH_CLIENTID_SDMA1 128 
 int /*<<< orphan*/  amdgpu_fence_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdma_v5_0_process_trap_irq(struct amdgpu_device *adev,
				      struct amdgpu_irq_src *source,
				      struct amdgpu_iv_entry *entry)
{
	DRM_DEBUG("IH: SDMA trap\n");
	switch (entry->client_id) {
	case SOC15_IH_CLIENTID_SDMA0:
		switch (entry->ring_id) {
		case 0:
			amdgpu_fence_process(&adev->sdma.instance[0].ring);
			break;
		case 1:
			/* XXX compute */
			break;
		case 2:
			/* XXX compute */
			break;
		case 3:
			/* XXX page queue*/
			break;
		}
		break;
	case SOC15_IH_CLIENTID_SDMA1:
		switch (entry->ring_id) {
		case 0:
			amdgpu_fence_process(&adev->sdma.instance[1].ring);
			break;
		case 1:
			/* XXX compute */
			break;
		case 2:
			/* XXX compute */
			break;
		case 3:
			/* XXX page queue*/
			break;
		}
		break;
	}
	return 0;
}
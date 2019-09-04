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
struct TYPE_2__ {int /*<<< orphan*/  rcv_irq; int /*<<< orphan*/  ack_irq; } ;
struct amdgpu_device {TYPE_1__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOC15_IH_CLIENTID_BIF ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int xgpu_ai_mailbox_add_irq_id(struct amdgpu_device *adev)
{
	int r;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_BIF, 135, &adev->virt.rcv_irq);
	if (r)
		return r;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_BIF, 138, &adev->virt.ack_irq);
	if (r) {
		amdgpu_irq_put(adev, &adev->virt.rcv_irq, 0);
		return r;
	}

	return 0;
}
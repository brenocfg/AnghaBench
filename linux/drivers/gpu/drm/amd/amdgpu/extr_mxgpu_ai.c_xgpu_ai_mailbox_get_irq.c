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
struct TYPE_2__ {int /*<<< orphan*/  flr_work; int /*<<< orphan*/  rcv_irq; int /*<<< orphan*/  ack_irq; } ;
struct amdgpu_device {TYPE_1__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int amdgpu_irq_get (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgpu_ai_mailbox_flr_work ; 

int xgpu_ai_mailbox_get_irq(struct amdgpu_device *adev)
{
	int r;

	r = amdgpu_irq_get(adev, &adev->virt.rcv_irq, 0);
	if (r)
		return r;
	r = amdgpu_irq_get(adev, &adev->virt.ack_irq, 0);
	if (r) {
		amdgpu_irq_put(adev, &adev->virt.rcv_irq, 0);
		return r;
	}

	INIT_WORK(&adev->virt.flr_work, xgpu_ai_mailbox_flr_work);

	return 0;
}
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
struct amdgpu_irq_src {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct amdgpu_device {TYPE_2__ irq; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;
struct TYPE_3__ {int (* set ) (struct amdgpu_device*,struct amdgpu_irq_src*,unsigned int,int) ;} ;

/* Variables and functions */
 int AMDGPU_IRQ_STATE_DISABLE ; 
 int AMDGPU_IRQ_STATE_ENABLE ; 
 scalar_t__ amdgpu_irq_enabled (struct amdgpu_device*,struct amdgpu_irq_src*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct amdgpu_device*,struct amdgpu_irq_src*,unsigned int,int) ; 

int amdgpu_irq_update(struct amdgpu_device *adev,
			     struct amdgpu_irq_src *src, unsigned type)
{
	unsigned long irqflags;
	enum amdgpu_interrupt_state state;
	int r;

	spin_lock_irqsave(&adev->irq.lock, irqflags);

	/* We need to determine after taking the lock, otherwise
	   we might disable just enabled interrupts again */
	if (amdgpu_irq_enabled(adev, src, type))
		state = AMDGPU_IRQ_STATE_ENABLE;
	else
		state = AMDGPU_IRQ_STATE_DISABLE;

	r = src->funcs->set(adev, src, type, state);
	spin_unlock_irqrestore(&adev->irq.lock, irqflags);
	return r;
}
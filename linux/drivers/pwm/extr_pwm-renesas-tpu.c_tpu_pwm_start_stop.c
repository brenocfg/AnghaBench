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
typedef  int u16 ;
struct tpu_pwm_device {int channel; TYPE_1__* tpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TPU_TSTR ; 
 int ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tpu_pwm_start_stop(struct tpu_pwm_device *pwm, int start)
{
	unsigned long flags;
	u16 value;

	spin_lock_irqsave(&pwm->tpu->lock, flags);
	value = ioread16(pwm->tpu->base + TPU_TSTR);

	if (start)
		value |= 1 << pwm->channel;
	else
		value &= ~(1 << pwm->channel);

	iowrite16(value, pwm->tpu->base + TPU_TSTR);
	spin_unlock_irqrestore(&pwm->tpu->lock, flags);
}
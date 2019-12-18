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
typedef  int /*<<< orphan*/  u32 ;
struct rc_dev {struct ite_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_duty_cycle; } ;
struct ite_dev {int /*<<< orphan*/  lock; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ite_set_carrier_params (struct ite_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ite_set_tx_duty_cycle(struct rc_dev *rcdev, u32 duty_cycle)
{
	unsigned long flags;
	struct ite_dev *dev = rcdev->priv;

	spin_lock_irqsave(&dev->lock, flags);
	dev->params.tx_duty_cycle = duty_cycle;
	ite_set_carrier_params(dev);
	spin_unlock_irqrestore(&dev->lock, flags);

	return 0;
}
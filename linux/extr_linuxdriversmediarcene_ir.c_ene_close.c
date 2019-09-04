#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rc_dev {struct ene_device* priv; } ;
struct ene_device {int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ene_rx_disable (struct ene_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ene_close(struct rc_dev *rdev)
{
	struct ene_device *dev = rdev->priv;
	unsigned long flags;
	spin_lock_irqsave(&dev->hw_lock, flags);

	ene_rx_disable(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);
}
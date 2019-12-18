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
struct ene_device {int learning_mode_enabled; int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ene_rx_disable (struct ene_device*) ; 
 int /*<<< orphan*/  ene_rx_enable (struct ene_device*) ; 
 int /*<<< orphan*/  ene_rx_setup (struct ene_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ene_set_learning_mode(struct rc_dev *rdev, int enable)
{
	struct ene_device *dev = rdev->priv;
	unsigned long flags;
	if (enable == dev->learning_mode_enabled)
		return 0;

	spin_lock_irqsave(&dev->hw_lock, flags);
	dev->learning_mode_enabled = enable;
	ene_rx_disable(dev);
	ene_rx_setup(dev);
	ene_rx_enable(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);
	return 0;
}
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
struct ene_device {unsigned int* tx_buffer; unsigned int tx_len; int tx_sample_pulse; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  tx_complete; scalar_t__ tx_sample; scalar_t__ tx_done; scalar_t__ tx_reg; scalar_t__ tx_pos; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  ene_tx_disable (struct ene_device*) ; 
 int /*<<< orphan*/  ene_tx_enable (struct ene_device*) ; 
 int /*<<< orphan*/  ene_tx_sample (struct ene_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ene_transmit(struct rc_dev *rdev, unsigned *buf, unsigned n)
{
	struct ene_device *dev = rdev->priv;
	unsigned long flags;

	dev->tx_buffer = buf;
	dev->tx_len = n;
	dev->tx_pos = 0;
	dev->tx_reg = 0;
	dev->tx_done = 0;
	dev->tx_sample = 0;
	dev->tx_sample_pulse = false;

	dbg("TX: %d samples", dev->tx_len);

	spin_lock_irqsave(&dev->hw_lock, flags);

	ene_tx_enable(dev);

	/* Transmit first two samples */
	ene_tx_sample(dev);
	ene_tx_sample(dev);

	spin_unlock_irqrestore(&dev->hw_lock, flags);

	if (wait_for_completion_timeout(&dev->tx_complete, 2 * HZ) == 0) {
		dbg("TX: timeout");
		spin_lock_irqsave(&dev->hw_lock, flags);
		ene_tx_disable(dev);
		spin_unlock_irqrestore(&dev->hw_lock, flags);
	} else
		dbg("TX: done");
	return n;
}
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
struct bcm2835_host {int irq_block; int irq_busy; int irq_data; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bcm2835_block_irq (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_busy_irq (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_data_threaded_irq (struct bcm2835_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t bcm2835_threaded_irq(int irq, void *dev_id)
{
	struct bcm2835_host *host = dev_id;
	unsigned long flags;
	bool block, busy, data;

	spin_lock_irqsave(&host->lock, flags);

	block = host->irq_block;
	busy  = host->irq_busy;
	data  = host->irq_data;
	host->irq_block = false;
	host->irq_busy  = false;
	host->irq_data  = false;

	spin_unlock_irqrestore(&host->lock, flags);

	mutex_lock(&host->mutex);

	if (block)
		bcm2835_block_irq(host);
	if (busy)
		bcm2835_busy_irq(host);
	if (data)
		bcm2835_data_threaded_irq(host);

	mutex_unlock(&host->mutex);

	return IRQ_HANDLED;
}
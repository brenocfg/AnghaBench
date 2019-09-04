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
struct ad7877 {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; TYPE_1__* spi; int /*<<< orphan*/  msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TS_PEN_UP_TIMEOUT ; 
 int ad7877_process_data (struct ad7877*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int spi_sync (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t ad7877_irq(int irq, void *handle)
{
	struct ad7877 *ts = handle;
	unsigned long flags;
	int error;

	error = spi_sync(ts->spi, &ts->msg);
	if (error) {
		dev_err(&ts->spi->dev, "spi_sync --> %d\n", error);
		goto out;
	}

	spin_lock_irqsave(&ts->lock, flags);
	error = ad7877_process_data(ts);
	if (!error)
		mod_timer(&ts->timer, jiffies + TS_PEN_UP_TIMEOUT);
	spin_unlock_irqrestore(&ts->lock, flags);

out:
	return IRQ_HANDLED;
}
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
struct mpc52xx_spi {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mpc52xx_spi_fsm_process (int,struct mpc52xx_spi*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mpc52xx_spi_irq(int irq, void *_ms)
{
	struct mpc52xx_spi *ms = _ms;
	spin_lock(&ms->lock);
	mpc52xx_spi_fsm_process(irq, ms);
	spin_unlock(&ms->lock);
	return IRQ_HANDLED;
}
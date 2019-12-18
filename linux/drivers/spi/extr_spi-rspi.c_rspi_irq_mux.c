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
typedef  int u8 ;
struct rspi_data {int spsr; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  RSPI_SPSR ; 
 int SPCR_SPRIE ; 
 int SPCR_SPTIE ; 
 int SPSR_SPRF ; 
 int SPSR_SPTEF ; 
 int /*<<< orphan*/  rspi_disable_irq (struct rspi_data*,int) ; 
 int rspi_read8 (struct rspi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rspi_irq_mux(int irq, void *_sr)
{
	struct rspi_data *rspi = _sr;
	u8 spsr;
	irqreturn_t ret = IRQ_NONE;
	u8 disable_irq = 0;

	rspi->spsr = spsr = rspi_read8(rspi, RSPI_SPSR);
	if (spsr & SPSR_SPRF)
		disable_irq |= SPCR_SPRIE;
	if (spsr & SPSR_SPTEF)
		disable_irq |= SPCR_SPTIE;

	if (disable_irq) {
		ret = IRQ_HANDLED;
		rspi_disable_irq(rspi, disable_irq);
		wake_up(&rspi->wait);
	}

	return ret;
}
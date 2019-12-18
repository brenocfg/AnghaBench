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
typedef  int u32 ;
struct pluto {int dead; scalar_t__ overflow; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  REG_TSCR ; 
 int TSCR_DE ; 
 int TSCR_IACK ; 
 int TSCR_NBPACKETS ; 
 int TSCR_OVR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  pluto_dma_end (struct pluto*,int) ; 
 int pluto_readreg (struct pluto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_reset_ts (struct pluto*,int) ; 
 int /*<<< orphan*/  pluto_write_tscr (struct pluto*,int) ; 

__attribute__((used)) static irqreturn_t pluto_irq(int irq, void *dev_id)
{
	struct pluto *pluto = dev_id;
	u32 tscr;

	/* check whether an interrupt occurred on this device */
	tscr = pluto_readreg(pluto, REG_TSCR);
	if (!(tscr & (TSCR_DE | TSCR_OVR)))
		return IRQ_NONE;

	if (tscr == 0xffffffff) {
		if (pluto->dead == 0)
			dev_err(&pluto->pdev->dev, "card has hung or been ejected.\n");
		/* It's dead Jim */
		pluto->dead = 1;
		return IRQ_HANDLED;
	}

	/* dma end interrupt */
	if (tscr & TSCR_DE) {
		pluto_dma_end(pluto, (tscr & TSCR_NBPACKETS) >> 24);
		/* overflow interrupt */
		if (tscr & TSCR_OVR)
			pluto->overflow++;
		if (pluto->overflow) {
			dev_err(&pluto->pdev->dev, "overflow irq (%d)\n",
					pluto->overflow);
			pluto_reset_ts(pluto, 1);
			pluto->overflow = 0;
		}
	} else if (tscr & TSCR_OVR) {
		pluto->overflow++;
	}

	/* ACK the interrupt */
	pluto_write_tscr(pluto, tscr | TSCR_IACK);

	return IRQ_HANDLED;
}
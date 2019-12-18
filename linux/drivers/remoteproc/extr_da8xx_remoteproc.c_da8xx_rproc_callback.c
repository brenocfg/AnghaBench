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
typedef  int u32 ;
struct rproc {scalar_t__ priv; } ;
struct da8xx_rproc {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  (* ack_fxn ) (int /*<<< orphan*/ ) ;scalar_t__ chipsig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int SYSCFG_CHIPSIG0 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t da8xx_rproc_callback(int irq, void *p)
{
	struct rproc *rproc = (struct rproc *)p;
	struct da8xx_rproc *drproc = (struct da8xx_rproc *)rproc->priv;
	u32 chipsig;

	chipsig = readl(drproc->chipsig);
	if (chipsig & SYSCFG_CHIPSIG0) {
		/* Clear interrupt level source */
		writel(SYSCFG_CHIPSIG0, drproc->chipsig + 4);

		/*
		 * ACK intr to AINTC.
		 *
		 * It has already been ack'ed by the kernel before calling
		 * this function, but since the ARM<->DSP interrupts in the
		 * CHIPSIG register are "level" instead of "pulse" variety,
		 * we need to ack it after taking down the level else we'll
		 * be called again immediately after returning.
		 */
		drproc->ack_fxn(drproc->irq_data);

		return IRQ_WAKE_THREAD;
	}

	return IRQ_HANDLED;
}
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
struct pxa3xx_gcu_shared {int /*<<< orphan*/  num_done; scalar_t__ hw_running; int /*<<< orphan*/  num_idle; int /*<<< orphan*/  num_interrupts; } ;
struct pxa3xx_gcu_priv {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  wait_idle; scalar_t__ ready; int /*<<< orphan*/  wait_free; struct pxa3xx_gcu_shared* shared; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int IE_ALL ; 
 int IE_EEOB ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  QDUMP (char*) ; 
 int /*<<< orphan*/  QERROR (char*) ; 
 int /*<<< orphan*/  REG_GCISCR ; 
 int /*<<< orphan*/  REG_GCRBLR ; 
 int /*<<< orphan*/  dump_whole_state (struct pxa3xx_gcu_priv*) ; 
 int /*<<< orphan*/  flush_running (struct pxa3xx_gcu_priv*) ; 
 int gc_readl (struct pxa3xx_gcu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_writel (struct pxa3xx_gcu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  run_ready (struct pxa3xx_gcu_priv*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
pxa3xx_gcu_handle_irq(int irq, void *ctx)
{
	struct pxa3xx_gcu_priv *priv = ctx;
	struct pxa3xx_gcu_shared *shared = priv->shared;
	u32 status = gc_readl(priv, REG_GCISCR) & IE_ALL;

	QDUMP("-Interrupt");

	if (!status)
		return IRQ_NONE;

	spin_lock(&priv->spinlock);
	shared->num_interrupts++;

	if (status & IE_EEOB) {
		QDUMP(" [EEOB]");

		flush_running(priv);
		wake_up_all(&priv->wait_free);

		if (priv->ready) {
			run_ready(priv);
		} else {
			/* There is no more data prepared by the userspace.
			 * Set hw_running = 0 and wait for the next userspace
			 * kick-off */
			shared->num_idle++;
			shared->hw_running = 0;

			QDUMP(" '-> Idle.");

			/* set ring buffer length to zero */
			gc_writel(priv, REG_GCRBLR, 0);

			wake_up_all(&priv->wait_idle);
		}

		shared->num_done++;
	} else {
		QERROR(" [???]");
		dump_whole_state(priv);
	}

	/* Clear the interrupt */
	gc_writel(priv, REG_GCISCR, status);
	spin_unlock(&priv->spinlock);

	return IRQ_HANDLED;
}
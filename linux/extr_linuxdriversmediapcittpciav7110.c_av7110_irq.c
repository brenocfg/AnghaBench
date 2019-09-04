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
struct saa7146_dev {struct av7110* ext_priv; } ;
struct av7110 {int /*<<< orphan*/  vpe_tasklet; int /*<<< orphan*/  gpio_tasklet; int /*<<< orphan*/  debi_tasklet; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MASK_03 ; 
 int MASK_10 ; 
 int MASK_19 ; 
 int /*<<< orphan*/  SAA7146_IER_DISABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SAA7146_ISR_CLEAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void av7110_irq(struct saa7146_dev* dev, u32 *isr)
{
	struct av7110 *av7110 = dev->ext_priv;

	//print_time("av7110_irq");

	/* Note: Don't try to handle the DEBI error irq (MASK_18), in
	 * intel mode the timeout is asserted all the time...
	 */

	if (*isr & MASK_19) {
		//printk("av7110_irq: DEBI\n");
		/* Note 1: The DEBI irq is level triggered: We must enable it
		 * only after we started a DMA xfer, and disable it here
		 * immediately, or it will be signalled all the time while
		 * DEBI is idle.
		 * Note 2: You would think that an irq which is masked is
		 * not signalled by the hardware. Not so for the SAA7146:
		 * An irq is signalled as long as the corresponding bit
		 * in the ISR is set, and disabling irqs just prevents the
		 * hardware from setting the ISR bit. This means a) that we
		 * must clear the ISR *after* disabling the irq (which is why
		 * we must do it here even though saa7146_core did it already),
		 * and b) that if we were to disable an edge triggered irq
		 * (like the gpio irqs sadly are) temporarily we would likely
		 * loose some. This sucks :-(
		 */
		SAA7146_IER_DISABLE(av7110->dev, MASK_19);
		SAA7146_ISR_CLEAR(av7110->dev, MASK_19);
		tasklet_schedule(&av7110->debi_tasklet);
	}

	if (*isr & MASK_03) {
		//printk("av7110_irq: GPIO\n");
		tasklet_schedule(&av7110->gpio_tasklet);
	}

	if (*isr & MASK_10)
		tasklet_schedule(&av7110->vpe_tasklet);
}
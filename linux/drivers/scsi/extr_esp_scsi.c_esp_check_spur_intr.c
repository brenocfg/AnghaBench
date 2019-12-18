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
struct esp {int rev; int sreg; int ireg; int /*<<< orphan*/  host; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_error ) (struct esp*) ;} ;

/* Variables and functions */
#define  ESP100 129 
#define  ESP100A 128 
 int ESP_INTR_SR ; 
 int ESP_STAT_INTR ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct esp*) ; 

__attribute__((used)) static int esp_check_spur_intr(struct esp *esp)
{
	switch (esp->rev) {
	case ESP100:
	case ESP100A:
		/* The interrupt pending bit of the status register cannot
		 * be trusted on these revisions.
		 */
		esp->sreg &= ~ESP_STAT_INTR;
		break;

	default:
		if (!(esp->sreg & ESP_STAT_INTR)) {
			if (esp->ireg & ESP_INTR_SR)
				return 1;

			/* If the DMA is indicating interrupt pending and the
			 * ESP is not, the only possibility is a DMA error.
			 */
			if (!esp->ops->dma_error(esp)) {
				shost_printk(KERN_ERR, esp->host,
					     "Spurious irq, sreg=%02x.\n",
					     esp->sreg);
				return -1;
			}

			shost_printk(KERN_ERR, esp->host, "DMA error\n");

			/* XXX Reset the chip. XXX */
			return -1;
		}
		break;
	}

	return 0;
}
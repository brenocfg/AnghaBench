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
struct parport_ip32_private {int /*<<< orphan*/  irq_mode; int /*<<< orphan*/  irq_complete; } ;
struct parport {TYPE_1__* cad; struct parport* physport; struct parport_ip32_private* private_data; } ;
struct TYPE_2__ {unsigned long timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 unsigned int ECR_DMAEN ; 
 unsigned int ECR_SERVINTR ; 
 int /*<<< orphan*/  FIFO_NFAULT_TIMEOUT ; 
 int /*<<< orphan*/  PARPORT_IP32_IRQ_FWD ; 
 int /*<<< orphan*/  PARPORT_IP32_IRQ_HERE ; 
 unsigned long jiffies ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 size_t parport_ip32_dma_get_residue () ; 
 int /*<<< orphan*/  parport_ip32_dma_start (struct parport*,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  parport_ip32_dma_stop (struct parport*) ; 
 scalar_t__ parport_ip32_fifo_wait_break (struct parport*,unsigned long) ; 
 int /*<<< orphan*/  parport_ip32_frob_econtrol (struct parport*,unsigned int,unsigned int) ; 
 unsigned int parport_ip32_read_econtrol (struct parport*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static size_t parport_ip32_fifo_write_block_dma(struct parport *p,
						const void *buf, size_t len)
{
	struct parport_ip32_private * const priv = p->physport->private_data;
	struct parport * const physport = p->physport;
	unsigned long nfault_timeout;
	unsigned long expire;
	size_t written;
	unsigned int ecr;

	priv->irq_mode = PARPORT_IP32_IRQ_HERE;

	parport_ip32_dma_start(p, DMA_TO_DEVICE, (void *)buf, len);
	reinit_completion(&priv->irq_complete);
	parport_ip32_frob_econtrol(p, ECR_DMAEN | ECR_SERVINTR, ECR_DMAEN);

	nfault_timeout = min((unsigned long)physport->cad->timeout,
			     msecs_to_jiffies(FIFO_NFAULT_TIMEOUT));
	expire = jiffies + physport->cad->timeout;
	while (1) {
		if (parport_ip32_fifo_wait_break(p, expire))
			break;
		wait_for_completion_interruptible_timeout(&priv->irq_complete,
							  nfault_timeout);
		ecr = parport_ip32_read_econtrol(p);
		if (ecr & ECR_SERVINTR)
			break;	/* DMA transfer just finished */
	}
	parport_ip32_dma_stop(p);
	written = len - parport_ip32_dma_get_residue();

	priv->irq_mode = PARPORT_IP32_IRQ_FWD;

	return written;
}
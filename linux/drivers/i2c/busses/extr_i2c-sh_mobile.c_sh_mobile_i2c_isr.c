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
struct sh_mobile_i2c_data {unsigned char sr; int pos; scalar_t__ dma_direction; int /*<<< orphan*/  wait; TYPE_1__* msg; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  ICIC ; 
 int /*<<< orphan*/  ICIC_RDMAE ; 
 int /*<<< orphan*/  ICIC_TDMAE ; 
 int /*<<< orphan*/  ICSR ; 
 unsigned char ICSR_AL ; 
 unsigned char ICSR_TACK ; 
 unsigned char ICSR_WAIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char SW_DONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,unsigned char,char*,int,int /*<<< orphan*/ ) ; 
 unsigned char iic_rd (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iic_set_clr (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iic_wr (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ,unsigned char) ; 
 int sh_mobile_i2c_isr_rx (struct sh_mobile_i2c_data*) ; 
 int sh_mobile_i2c_isr_tx (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sh_mobile_i2c_isr(int irq, void *dev_id)
{
	struct sh_mobile_i2c_data *pd = dev_id;
	unsigned char sr;
	int wakeup = 0;

	sr = iic_rd(pd, ICSR);
	pd->sr |= sr; /* remember state */

	dev_dbg(pd->dev, "i2c_isr 0x%02x 0x%02x %s %d %d!\n", sr, pd->sr,
	       (pd->msg->flags & I2C_M_RD) ? "read" : "write",
	       pd->pos, pd->msg->len);

	/* Kick off TxDMA after preface was done */
	if (pd->dma_direction == DMA_TO_DEVICE && pd->pos == 0)
		iic_set_clr(pd, ICIC, ICIC_TDMAE, 0);
	else if (sr & (ICSR_AL | ICSR_TACK))
		/* don't interrupt transaction - continue to issue stop */
		iic_wr(pd, ICSR, sr & ~(ICSR_AL | ICSR_TACK));
	else if (pd->msg->flags & I2C_M_RD)
		wakeup = sh_mobile_i2c_isr_rx(pd);
	else
		wakeup = sh_mobile_i2c_isr_tx(pd);

	/* Kick off RxDMA after preface was done */
	if (pd->dma_direction == DMA_FROM_DEVICE && pd->pos == 1)
		iic_set_clr(pd, ICIC, ICIC_RDMAE, 0);

	if (sr & ICSR_WAIT) /* TODO: add delay here to support slow acks */
		iic_wr(pd, ICSR, sr & ~ICSR_WAIT);

	if (wakeup) {
		pd->sr |= SW_DONE;
		wake_up(&pd->wait);
	}

	/* defeat write posting to avoid spurious WAIT interrupts */
	iic_rd(pd, ICSR);

	return IRQ_HANDLED;
}
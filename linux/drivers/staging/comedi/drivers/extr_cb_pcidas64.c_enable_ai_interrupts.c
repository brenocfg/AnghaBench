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
struct pcidas64_private {int intr_enable_bits; scalar_t__ main_iobase; } ;
struct pcidas64_board {scalar_t__ layout; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct pcidas64_private* private; struct pcidas64_board* board_ptr; } ;
struct comedi_cmd {int flags; } ;

/* Variables and functions */
 int ADC_INTR_EOSCAN_BITS ; 
 int CMDF_WAKE_EOS ; 
 int EN_ADC_ACTIVE_INTR_BIT ; 
 int EN_ADC_DONE_INTR_BIT ; 
 int EN_ADC_INTR_SRC_BIT ; 
 int EN_ADC_OVERRUN_BIT ; 
 int EN_ADC_STOP_INTR_BIT ; 
 scalar_t__ INTR_ENABLE_REG ; 
 scalar_t__ LAYOUT_4020 ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void enable_ai_interrupts(struct comedi_device *dev,
				 const struct comedi_cmd *cmd)
{
	const struct pcidas64_board *board = dev->board_ptr;
	struct pcidas64_private *devpriv = dev->private;
	u32 bits;
	unsigned long flags;

	bits = EN_ADC_OVERRUN_BIT | EN_ADC_DONE_INTR_BIT |
	       EN_ADC_ACTIVE_INTR_BIT | EN_ADC_STOP_INTR_BIT;
	/*
	 * Use pio transfer and interrupt on end of conversion
	 * if CMDF_WAKE_EOS flag is set.
	 */
	if (cmd->flags & CMDF_WAKE_EOS) {
		/* 4020 doesn't support pio transfers except for fifo dregs */
		if (board->layout != LAYOUT_4020)
			bits |= ADC_INTR_EOSCAN_BITS | EN_ADC_INTR_SRC_BIT;
	}
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->intr_enable_bits |= bits;
	writew(devpriv->intr_enable_bits,
	       devpriv->main_iobase + INTR_ENABLE_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);
}
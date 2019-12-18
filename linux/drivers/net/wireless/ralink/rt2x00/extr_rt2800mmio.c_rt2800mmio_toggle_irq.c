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
typedef  scalar_t__ u32 ;
struct rt2x00_dev {int /*<<< orphan*/  pretbtt_tasklet; int /*<<< orphan*/  tbtt_tasklet; int /*<<< orphan*/  autowake_tasklet; int /*<<< orphan*/  rxdone_tasklet; int /*<<< orphan*/  txstatus_tasklet; int /*<<< orphan*/  irqmask_lock; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK_CSR ; 
 int /*<<< orphan*/  INT_MASK_CSR_AUTO_WAKEUP ; 
 int /*<<< orphan*/  INT_MASK_CSR_PRE_TBTT ; 
 int /*<<< orphan*/  INT_MASK_CSR_RX_DONE ; 
 int /*<<< orphan*/  INT_MASK_CSR_TBTT ; 
 int /*<<< orphan*/  INT_MASK_CSR_TX_FIFO_STATUS ; 
 int /*<<< orphan*/  INT_SOURCE_CSR ; 
 int STATE_RADIO_IRQ_OFF ; 
 int STATE_RADIO_IRQ_ON ; 
 int /*<<< orphan*/  rt2x00_set_field32 (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void rt2800mmio_toggle_irq(struct rt2x00_dev *rt2x00dev,
			   enum dev_state state)
{
	u32 reg;
	unsigned long flags;

	/*
	 * When interrupts are being enabled, the interrupt registers
	 * should clear the register to assure a clean state.
	 */
	if (state == STATE_RADIO_IRQ_ON) {
		reg = rt2x00mmio_register_read(rt2x00dev, INT_SOURCE_CSR);
		rt2x00mmio_register_write(rt2x00dev, INT_SOURCE_CSR, reg);
	}

	spin_lock_irqsave(&rt2x00dev->irqmask_lock, flags);
	reg = 0;
	if (state == STATE_RADIO_IRQ_ON) {
		rt2x00_set_field32(&reg, INT_MASK_CSR_RX_DONE, 1);
		rt2x00_set_field32(&reg, INT_MASK_CSR_TBTT, 1);
		rt2x00_set_field32(&reg, INT_MASK_CSR_PRE_TBTT, 1);
		rt2x00_set_field32(&reg, INT_MASK_CSR_TX_FIFO_STATUS, 1);
		rt2x00_set_field32(&reg, INT_MASK_CSR_AUTO_WAKEUP, 1);
	}
	rt2x00mmio_register_write(rt2x00dev, INT_MASK_CSR, reg);
	spin_unlock_irqrestore(&rt2x00dev->irqmask_lock, flags);

	if (state == STATE_RADIO_IRQ_OFF) {
		/*
		 * Wait for possibly running tasklets to finish.
		 */
		tasklet_kill(&rt2x00dev->txstatus_tasklet);
		tasklet_kill(&rt2x00dev->rxdone_tasklet);
		tasklet_kill(&rt2x00dev->autowake_tasklet);
		tasklet_kill(&rt2x00dev->tbtt_tasklet);
		tasklet_kill(&rt2x00dev->pretbtt_tasklet);
	}
}
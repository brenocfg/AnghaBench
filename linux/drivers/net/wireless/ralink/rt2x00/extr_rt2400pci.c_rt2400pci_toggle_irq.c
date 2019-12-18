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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int /*<<< orphan*/  tbtt_tasklet; int /*<<< orphan*/  rxdone_tasklet; int /*<<< orphan*/  txstatus_tasklet; int /*<<< orphan*/  irqmask_lock; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;

/* Variables and functions */
 int /*<<< orphan*/  CSR7 ; 
 int /*<<< orphan*/  CSR8 ; 
 int /*<<< orphan*/  CSR8_RXDONE ; 
 int /*<<< orphan*/  CSR8_TBCN_EXPIRE ; 
 int /*<<< orphan*/  CSR8_TXDONE_ATIMRING ; 
 int /*<<< orphan*/  CSR8_TXDONE_PRIORING ; 
 int /*<<< orphan*/  CSR8_TXDONE_TXRING ; 
 int STATE_RADIO_IRQ_OFF ; 
 int STATE_RADIO_IRQ_ON ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2400pci_toggle_irq(struct rt2x00_dev *rt2x00dev,
				 enum dev_state state)
{
	int mask = (state == STATE_RADIO_IRQ_OFF);
	u32 reg;
	unsigned long flags;

	/*
	 * When interrupts are being enabled, the interrupt registers
	 * should clear the register to assure a clean state.
	 */
	if (state == STATE_RADIO_IRQ_ON) {
		reg = rt2x00mmio_register_read(rt2x00dev, CSR7);
		rt2x00mmio_register_write(rt2x00dev, CSR7, reg);
	}

	/*
	 * Only toggle the interrupts bits we are going to use.
	 * Non-checked interrupt bits are disabled by default.
	 */
	spin_lock_irqsave(&rt2x00dev->irqmask_lock, flags);

	reg = rt2x00mmio_register_read(rt2x00dev, CSR8);
	rt2x00_set_field32(&reg, CSR8_TBCN_EXPIRE, mask);
	rt2x00_set_field32(&reg, CSR8_TXDONE_TXRING, mask);
	rt2x00_set_field32(&reg, CSR8_TXDONE_ATIMRING, mask);
	rt2x00_set_field32(&reg, CSR8_TXDONE_PRIORING, mask);
	rt2x00_set_field32(&reg, CSR8_RXDONE, mask);
	rt2x00mmio_register_write(rt2x00dev, CSR8, reg);

	spin_unlock_irqrestore(&rt2x00dev->irqmask_lock, flags);

	if (state == STATE_RADIO_IRQ_OFF) {
		/*
		 * Ensure that all tasklets are finished before
		 * disabling the interrupts.
		 */
		tasklet_kill(&rt2x00dev->txstatus_tasklet);
		tasklet_kill(&rt2x00dev->rxdone_tasklet);
		tasklet_kill(&rt2x00dev->tbtt_tasklet);
	}
}
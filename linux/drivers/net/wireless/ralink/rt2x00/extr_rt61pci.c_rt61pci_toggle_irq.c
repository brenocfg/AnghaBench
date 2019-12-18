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
struct rt2x00_dev {int /*<<< orphan*/  tbtt_tasklet; int /*<<< orphan*/  autowake_tasklet; int /*<<< orphan*/  rxdone_tasklet; int /*<<< orphan*/  txstatus_tasklet; int /*<<< orphan*/  irqmask_lock; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK_CSR ; 
 int /*<<< orphan*/  INT_MASK_CSR_BEACON_DONE ; 
 int /*<<< orphan*/  INT_MASK_CSR_ENABLE_MITIGATION ; 
 int /*<<< orphan*/  INT_MASK_CSR_MITIGATION_PERIOD ; 
 int /*<<< orphan*/  INT_MASK_CSR_RXDONE ; 
 int /*<<< orphan*/  INT_MASK_CSR_TXDONE ; 
 int /*<<< orphan*/  INT_SOURCE_CSR ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_0 ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_1 ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_2 ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_3 ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_4 ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_5 ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_6 ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_7 ; 
 int /*<<< orphan*/  MCU_INT_MASK_CSR_TWAKEUP ; 
 int /*<<< orphan*/  MCU_INT_SOURCE_CSR ; 
 int STATE_RADIO_IRQ_OFF ; 
 int STATE_RADIO_IRQ_ON ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt61pci_toggle_irq(struct rt2x00_dev *rt2x00dev,
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
		reg = rt2x00mmio_register_read(rt2x00dev, INT_SOURCE_CSR);
		rt2x00mmio_register_write(rt2x00dev, INT_SOURCE_CSR, reg);

		reg = rt2x00mmio_register_read(rt2x00dev, MCU_INT_SOURCE_CSR);
		rt2x00mmio_register_write(rt2x00dev, MCU_INT_SOURCE_CSR, reg);
	}

	/*
	 * Only toggle the interrupts bits we are going to use.
	 * Non-checked interrupt bits are disabled by default.
	 */
	spin_lock_irqsave(&rt2x00dev->irqmask_lock, flags);

	reg = rt2x00mmio_register_read(rt2x00dev, INT_MASK_CSR);
	rt2x00_set_field32(&reg, INT_MASK_CSR_TXDONE, mask);
	rt2x00_set_field32(&reg, INT_MASK_CSR_RXDONE, mask);
	rt2x00_set_field32(&reg, INT_MASK_CSR_BEACON_DONE, mask);
	rt2x00_set_field32(&reg, INT_MASK_CSR_ENABLE_MITIGATION, mask);
	rt2x00_set_field32(&reg, INT_MASK_CSR_MITIGATION_PERIOD, 0xff);
	rt2x00mmio_register_write(rt2x00dev, INT_MASK_CSR, reg);

	reg = rt2x00mmio_register_read(rt2x00dev, MCU_INT_MASK_CSR);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_0, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_1, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_2, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_3, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_4, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_5, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_6, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_7, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_TWAKEUP, mask);
	rt2x00mmio_register_write(rt2x00dev, MCU_INT_MASK_CSR, reg);

	spin_unlock_irqrestore(&rt2x00dev->irqmask_lock, flags);

	if (state == STATE_RADIO_IRQ_OFF) {
		/*
		 * Ensure that all tasklets are finished.
		 */
		tasklet_kill(&rt2x00dev->txstatus_tasklet);
		tasklet_kill(&rt2x00dev->rxdone_tasklet);
		tasklet_kill(&rt2x00dev->autowake_tasklet);
		tasklet_kill(&rt2x00dev->tbtt_tasklet);
	}
}
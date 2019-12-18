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
struct rt2x00_dev {int /*<<< orphan*/  irqmask_lock; int /*<<< orphan*/  autowake_tasklet; int /*<<< orphan*/  rxdone_tasklet; int /*<<< orphan*/  tbtt_tasklet; int /*<<< orphan*/  pretbtt_tasklet; int /*<<< orphan*/  txstatus_tasklet; int /*<<< orphan*/  txstatus_fifo; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  INT_MASK_CSR ; 
 int /*<<< orphan*/  INT_MASK_CSR_TX_FIFO_STATUS ; 
 int /*<<< orphan*/  INT_SOURCE_CSR ; 
 int /*<<< orphan*/  INT_SOURCE_CSR_AUTO_WAKEUP ; 
 int /*<<< orphan*/  INT_SOURCE_CSR_PRE_TBTT ; 
 int /*<<< orphan*/  INT_SOURCE_CSR_RX_DONE ; 
 int /*<<< orphan*/  INT_SOURCE_CSR_TBTT ; 
 int /*<<< orphan*/  INT_SOURCE_CSR_TX_FIFO_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800mmio_fetch_txstatus (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t rt2800mmio_interrupt(int irq, void *dev_instance)
{
	struct rt2x00_dev *rt2x00dev = dev_instance;
	u32 reg, mask;

	/* Read status and ACK all interrupts */
	reg = rt2x00mmio_register_read(rt2x00dev, INT_SOURCE_CSR);
	rt2x00mmio_register_write(rt2x00dev, INT_SOURCE_CSR, reg);

	if (!reg)
		return IRQ_NONE;

	if (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		return IRQ_HANDLED;

	/*
	 * Since INT_MASK_CSR and INT_SOURCE_CSR use the same bits
	 * for interrupts and interrupt masks we can just use the value of
	 * INT_SOURCE_CSR to create the interrupt mask.
	 */
	mask = ~reg;

	if (rt2x00_get_field32(reg, INT_SOURCE_CSR_TX_FIFO_STATUS)) {
		rt2x00_set_field32(&mask, INT_MASK_CSR_TX_FIFO_STATUS, 1);
		rt2800mmio_fetch_txstatus(rt2x00dev);
		if (!kfifo_is_empty(&rt2x00dev->txstatus_fifo))
			tasklet_schedule(&rt2x00dev->txstatus_tasklet);
	}

	if (rt2x00_get_field32(reg, INT_SOURCE_CSR_PRE_TBTT))
		tasklet_hi_schedule(&rt2x00dev->pretbtt_tasklet);

	if (rt2x00_get_field32(reg, INT_SOURCE_CSR_TBTT))
		tasklet_hi_schedule(&rt2x00dev->tbtt_tasklet);

	if (rt2x00_get_field32(reg, INT_SOURCE_CSR_RX_DONE))
		tasklet_schedule(&rt2x00dev->rxdone_tasklet);

	if (rt2x00_get_field32(reg, INT_SOURCE_CSR_AUTO_WAKEUP))
		tasklet_schedule(&rt2x00dev->autowake_tasklet);

	/*
	 * Disable all interrupts for which a tasklet was scheduled right now,
	 * the tasklet will reenable the appropriate interrupts.
	 */
	spin_lock(&rt2x00dev->irqmask_lock);
	reg = rt2x00mmio_register_read(rt2x00dev, INT_MASK_CSR);
	reg &= mask;
	rt2x00mmio_register_write(rt2x00dev, INT_MASK_CSR, reg);
	spin_unlock(&rt2x00dev->irqmask_lock);

	return IRQ_HANDLED;
}
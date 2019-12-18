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
struct rt2x00_dev {int /*<<< orphan*/  irqmask_lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR8 ; 
 int /*<<< orphan*/  CSR8_TXDONE_ATIMRING ; 
 int /*<<< orphan*/  CSR8_TXDONE_PRIORING ; 
 int /*<<< orphan*/  CSR8_TXDONE_TXRING ; 
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  QID_AC_VI ; 
 int /*<<< orphan*/  QID_AC_VO ; 
 int /*<<< orphan*/  QID_ATIM ; 
 int /*<<< orphan*/  rt2500pci_txdone (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2500pci_txstatus_tasklet(unsigned long data)
{
	struct rt2x00_dev *rt2x00dev = (struct rt2x00_dev *)data;
	u32 reg;

	/*
	 * Handle all tx queues.
	 */
	rt2500pci_txdone(rt2x00dev, QID_ATIM);
	rt2500pci_txdone(rt2x00dev, QID_AC_VO);
	rt2500pci_txdone(rt2x00dev, QID_AC_VI);

	/*
	 * Enable all TXDONE interrupts again.
	 */
	if (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags)) {
		spin_lock_irq(&rt2x00dev->irqmask_lock);

		reg = rt2x00mmio_register_read(rt2x00dev, CSR8);
		rt2x00_set_field32(&reg, CSR8_TXDONE_TXRING, 0);
		rt2x00_set_field32(&reg, CSR8_TXDONE_ATIMRING, 0);
		rt2x00_set_field32(&reg, CSR8_TXDONE_PRIORING, 0);
		rt2x00mmio_register_write(rt2x00dev, CSR8, reg);

		spin_unlock_irq(&rt2x00dev->irqmask_lock);
	}
}
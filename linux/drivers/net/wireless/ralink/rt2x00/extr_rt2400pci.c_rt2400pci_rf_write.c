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
struct rt2x00_dev {int /*<<< orphan*/  csr_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFCSR ; 
 int /*<<< orphan*/  RFCSR_BUSY ; 
 int /*<<< orphan*/  RFCSR_IF_SELECT ; 
 int /*<<< orphan*/  RFCSR_NUMBER_OF_BITS ; 
 int /*<<< orphan*/  RFCSR_VALUE ; 
 scalar_t__ WAIT_FOR_RF (struct rt2x00_dev*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_rf_write (struct rt2x00_dev*,unsigned int const,int const) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2400pci_rf_write(struct rt2x00_dev *rt2x00dev,
			       const unsigned int word, const u32 value)
{
	u32 reg;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the RF becomes available, afterwards we
	 * can safely write the new data into the register.
	 */
	if (WAIT_FOR_RF(rt2x00dev, &reg)) {
		reg = 0;
		rt2x00_set_field32(&reg, RFCSR_VALUE, value);
		rt2x00_set_field32(&reg, RFCSR_NUMBER_OF_BITS, 20);
		rt2x00_set_field32(&reg, RFCSR_IF_SELECT, 0);
		rt2x00_set_field32(&reg, RFCSR_BUSY, 1);

		rt2x00mmio_register_write(rt2x00dev, RFCSR, reg);
		rt2x00_rf_write(rt2x00dev, word, value);
	}

	mutex_unlock(&rt2x00dev->csr_mutex);
}
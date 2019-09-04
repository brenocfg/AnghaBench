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

/* Variables and functions */
 int /*<<< orphan*/  HPET_ADDR ; 
 int /*<<< orphan*/  SMBUS_PCI_REG40 ; 
 int /*<<< orphan*/  SMBUS_PCI_REG64 ; 
 int /*<<< orphan*/  SMBUS_PCI_REGB4 ; 
 int /*<<< orphan*/  hpet_enable_legacy_int () ; 
 int /*<<< orphan*/  smbus_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smbus_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpet_setup(void)
{
	/* set hpet base address */
	smbus_write(SMBUS_PCI_REGB4, HPET_ADDR);

	/* enable decoding of access to HPET MMIO*/
	smbus_enable(SMBUS_PCI_REG40, (1 << 28));

	/* HPET irq enable */
	smbus_enable(SMBUS_PCI_REG64, (1 << 10));

	hpet_enable_legacy_int();
}
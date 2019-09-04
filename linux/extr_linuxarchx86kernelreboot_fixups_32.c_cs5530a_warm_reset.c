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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cs5530a_warm_reset(struct pci_dev *dev)
{
	/* writing 1 to the reset control register, 0x44 causes the
	cs5530a to perform a system warm reset */
	pci_write_config_byte(dev, 0x44, 0x1);
	udelay(50); /* shouldn't get here but be safe and spin-a-while */
	return;
}
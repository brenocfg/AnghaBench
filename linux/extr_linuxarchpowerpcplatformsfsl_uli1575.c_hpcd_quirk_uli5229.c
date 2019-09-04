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
 int /*<<< orphan*/  machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc86xx_hpcd ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,unsigned char) ; 

__attribute__((used)) static void hpcd_quirk_uli5229(struct pci_dev *dev)
{
	unsigned char c;

	if (!machine_is(mpc86xx_hpcd))
		return;

	pci_read_config_byte(dev, 0x4b, &c);
	c |= 0x10;
	pci_write_config_byte(dev, 0x4b, c);
}
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
struct octeon_device {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int cn6xxx_read_config_reg(char *s, struct octeon_device *oct)
{
	u32 val;
	int i, len = 0;

	/* PCI CONFIG Registers */

	len += sprintf(s + len,
		       "\n\t Octeon Config space Registers\n\n");

	for (i = 0; i <= 13; i++) {
		pci_read_config_dword(oct->pci_dev, (i * 4), &val);
		len += sprintf(s + len, "[0x%x] (Config[%d]): 0x%08x\n",
			       (i * 4), i, val);
	}

	for (i = 30; i <= 34; i++) {
		pci_read_config_dword(oct->pci_dev, (i * 4), &val);
		len += sprintf(s + len, "[0x%x] (Config[%d]): 0x%08x\n",
			       (i * 4), i, val);
	}

	return len;
}
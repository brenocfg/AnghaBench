#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ adapter_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCICFG_VPD_ADDR ; 
 int /*<<< orphan*/  A_PCICFG_VPD_DATA ; 
 int EEPROMSIZE ; 
 int EEPROM_MAX_POLL ; 
 int EINVAL ; 
 int EIO ; 
 int F_VPD_OP_FLAG ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int t1_seeprom_read(adapter_t *adapter, u32 addr, __le32 *data)
{
	int i = EEPROM_MAX_POLL;
	u16 val;
	u32 v;

	if (addr >= EEPROMSIZE || (addr & 3))
		return -EINVAL;

	pci_write_config_word(adapter->pdev, A_PCICFG_VPD_ADDR, (u16)addr);
	do {
		udelay(50);
		pci_read_config_word(adapter->pdev, A_PCICFG_VPD_ADDR, &val);
	} while (!(val & F_VPD_OP_FLAG) && --i);

	if (!(val & F_VPD_OP_FLAG)) {
		pr_err("%s: reading EEPROM address 0x%x failed\n",
		       adapter->name, addr);
		return -EIO;
	}
	pci_read_config_dword(adapter->pdev, A_PCICFG_VPD_DATA, &v);
	*data = cpu_to_le32(v);
	return 0;
}
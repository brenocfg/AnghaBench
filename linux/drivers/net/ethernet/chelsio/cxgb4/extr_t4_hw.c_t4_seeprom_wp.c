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
struct adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_STAT_ADDR ; 
 int pci_write_vpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 

int t4_seeprom_wp(struct adapter *adapter, bool enable)
{
	unsigned int v = enable ? 0xc : 0;
	int ret = pci_write_vpd(adapter->pdev, EEPROM_STAT_ADDR, 4, &v);
	return ret < 0 ? ret : 0;
}
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
typedef  int u8 ;
typedef  int u16 ;
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PHYADDR ; 
 int /*<<< orphan*/  PHYDATA0 ; 
 int /*<<< orphan*/  PHYDATA1 ; 
 int /*<<< orphan*/  PHYRWCTL ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_read_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 

int __rtsx_pci_write_phy_register(struct rtsx_pcr *pcr, u8 addr, u16 val)
{
	int err, i, finished = 0;
	u8 tmp;

	rtsx_pci_init_cmd(pcr);

	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PHYDATA0, 0xFF, (u8)val);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PHYDATA1, 0xFF, (u8)(val >> 8));
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PHYADDR, 0xFF, addr);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, PHYRWCTL, 0xFF, 0x81);

	err = rtsx_pci_send_cmd(pcr, 100);
	if (err < 0)
		return err;

	for (i = 0; i < 100000; i++) {
		err = rtsx_pci_read_register(pcr, PHYRWCTL, &tmp);
		if (err < 0)
			return err;

		if (!(tmp & 0x80)) {
			finished = 1;
			break;
		}
	}

	if (!finished)
		return -ETIMEDOUT;

	return 0;
}
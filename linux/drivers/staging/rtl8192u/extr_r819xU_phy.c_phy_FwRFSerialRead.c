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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
typedef  enum rf90_radio_path_e { ____Placeholder_rf90_radio_path_e } rf90_radio_path_e ;

/* Variables and functions */
 int /*<<< orphan*/  QPNR ; 
 int /*<<< orphan*/  RF_DATA ; 
 int /*<<< orphan*/  read_nic_dword (struct net_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 phy_FwRFSerialRead(struct net_device *dev,
			      enum rf90_radio_path_e e_rfpath,
			      u32 offset)
{
	u32		reg = 0;
	u32		data = 0;
	u8		time = 0;
	u32		tmp;

	/* Firmware RF Write control.
	 * We can not execute the scheme in the initial step.
	 * Otherwise, RF-R/W will waste much time.
	 * This is only for site survey.
	 */
	/* 1. Read operation need not insert data. bit 0-11 */
	/* 2. Write RF register address. bit 12-19 */
	data |= ((offset&0xFF)<<12);
	/* 3. Write RF path.  bit 20-21 */
	data |= ((e_rfpath&0x3)<<20);
	/* 4. Set RF read indicator. bit 22=0 */
	/* 5. Trigger Fw to operate the command. bit 31 */
	data |= 0x80000000;
	/* 6. We can not execute read operation if bit 31 is 1. */
	read_nic_dword(dev, QPNR, &tmp);
	while (tmp & 0x80000000) {
		/* If FW can not finish RF-R/W for more than ?? times.
		 * We must reset FW.
		 */
		if (time++ < 100) {
			udelay(10);
			read_nic_dword(dev, QPNR, &tmp);
		} else {
			break;
		}
	}
	/* 7. Execute read operation. */
	write_nic_dword(dev, QPNR, data);
	/* 8. Check if firmware send back RF content. */
	read_nic_dword(dev, QPNR, &tmp);
	while (tmp & 0x80000000) {
		/* If FW can not finish RF-R/W for more than ?? times.
		 * We must reset FW.
		 */
		if (time++ < 100) {
			udelay(10);
			read_nic_dword(dev, QPNR, &tmp);
		} else {
			return 0;
		}
	}
	read_nic_dword(dev, RF_DATA, &reg);

	return reg;
}
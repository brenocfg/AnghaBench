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
typedef  int u32 ;
struct smsc9420_pdata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int E2P_CMD_EPC_CMD_ERASE_ ; 
 int E2P_CMD_EPC_CMD_WRITE_ ; 
 int /*<<< orphan*/  E2P_DATA ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int smsc9420_eeprom_send_cmd (struct smsc9420_pdata*,int) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc9420_eeprom_write_location(struct smsc9420_pdata *pd,
					  u8 address, u8 data)
{
	u32 op = E2P_CMD_EPC_CMD_ERASE_ | address;
	int ret;

	netif_dbg(pd, hw, pd->dev, "address 0x%x, data 0x%x\n", address, data);
	ret = smsc9420_eeprom_send_cmd(pd, op);

	if (!ret) {
		op = E2P_CMD_EPC_CMD_WRITE_ | address;
		smsc9420_reg_write(pd, E2P_DATA, (u32)data);
		ret = smsc9420_eeprom_send_cmd(pd, op);
	}

	return ret;
}
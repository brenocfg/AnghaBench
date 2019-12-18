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
struct smsc9420_pdata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_CMD ; 
 int E2P_CMD_EPC_BUSY_ ; 
 int E2P_CMD_EPC_TIMEOUT_ ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netif_dbg (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_info (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_warn (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc9420_eeprom_send_cmd(struct smsc9420_pdata *pd, u32 op)
{
	int timeout = 100;
	u32 e2cmd;

	netif_dbg(pd, hw, pd->dev, "op 0x%08x\n", op);
	if (smsc9420_reg_read(pd, E2P_CMD) & E2P_CMD_EPC_BUSY_) {
		netif_warn(pd, hw, pd->dev, "Busy at start\n");
		return -EBUSY;
	}

	e2cmd = op | E2P_CMD_EPC_BUSY_;
	smsc9420_reg_write(pd, E2P_CMD, e2cmd);

	do {
		msleep(1);
		e2cmd = smsc9420_reg_read(pd, E2P_CMD);
	} while ((e2cmd & E2P_CMD_EPC_BUSY_) && (--timeout));

	if (!timeout) {
		netif_info(pd, hw, pd->dev, "TIMED OUT\n");
		return -EAGAIN;
	}

	if (e2cmd & E2P_CMD_EPC_TIMEOUT_) {
		netif_info(pd, hw, pd->dev,
			   "Error occurred during eeprom operation\n");
		return -EINVAL;
	}

	return 0;
}
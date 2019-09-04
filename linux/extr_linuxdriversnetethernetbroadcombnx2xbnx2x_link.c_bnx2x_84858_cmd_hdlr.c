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
typedef  scalar_t__ u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 scalar_t__ MDIO_848xx_CMD_HDLR_COMMAND ; 
 scalar_t__ MDIO_848xx_CMD_HDLR_DATA1 ; 
 scalar_t__ MDIO_848xx_CMD_HDLR_STATUS ; 
 int /*<<< orphan*/  MDIO_CTL_DEVAD ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ PHY84858_STATUS_CMD_COMPLETE_ERROR ; 
 scalar_t__ PHY84858_STATUS_CMD_COMPLETE_PASS ; 
 scalar_t__ PHY84858_STATUS_CMD_IN_PROGRESS ; 
 scalar_t__ PHY84858_STATUS_CMD_SYSTEM_BUSY ; 
 int PHY848xx_CMDHDLR_WAIT ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bnx2x_84858_cmd_hdlr(struct bnx2x_phy *phy,
				struct link_params *params,
				u16 fw_cmd,
				u16 cmd_args[], int argc)
{
	int idx;
	u16 val;
	struct bnx2x *bp = params->bp;

	/* Step 1: Poll the STATUS register to see whether the previous command
	 * is in progress or the system is busy (CMD_IN_PROGRESS or
	 * SYSTEM_BUSY). If previous command is in progress or system is busy,
	 * check again until the previous command finishes execution and the
	 * system is available for taking command
	 */

	for (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) {
		bnx2x_cl45_read(bp, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_STATUS, &val);
		if ((val != PHY84858_STATUS_CMD_IN_PROGRESS) &&
		    (val != PHY84858_STATUS_CMD_SYSTEM_BUSY))
			break;
		usleep_range(1000, 2000);
	}
	if (idx >= PHY848xx_CMDHDLR_WAIT) {
		DP(NETIF_MSG_LINK, "FW cmd: FW not ready.\n");
		return -EINVAL;
	}

	/* Step2: If any parameters are required for the function, write them
	 * to the required DATA registers
	 */

	for (idx = 0; idx < argc; idx++) {
		bnx2x_cl45_write(bp, phy, MDIO_CTL_DEVAD,
				 MDIO_848xx_CMD_HDLR_DATA1 + idx,
				 cmd_args[idx]);
	}

	/* Step3: When the firmware is ready for commands, write the 'Command
	 * code' to the CMD register
	 */
	bnx2x_cl45_write(bp, phy, MDIO_CTL_DEVAD,
			 MDIO_848xx_CMD_HDLR_COMMAND, fw_cmd);

	/* Step4: Once the command has been written, poll the STATUS register
	 * to check whether the command has completed (CMD_COMPLETED_PASS/
	 * CMD_FOR_CMDS or CMD_COMPLETED_ERROR).
	 */

	for (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) {
		bnx2x_cl45_read(bp, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_STATUS, &val);
		if ((val == PHY84858_STATUS_CMD_COMPLETE_PASS) ||
		    (val == PHY84858_STATUS_CMD_COMPLETE_ERROR))
			break;
		usleep_range(1000, 2000);
	}
	if ((idx >= PHY848xx_CMDHDLR_WAIT) ||
	    (val == PHY84858_STATUS_CMD_COMPLETE_ERROR)) {
		DP(NETIF_MSG_LINK, "FW cmd failed.\n");
		return -EINVAL;
	}
	/* Step5: Once the command has completed, read the specficied DATA
	 * registers for any saved results for the command, if applicable
	 */

	/* Gather returning data */
	for (idx = 0; idx < argc; idx++) {
		bnx2x_cl45_read(bp, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_DATA1 + idx,
				&cmd_args[idx]);
	}

	return 0;
}
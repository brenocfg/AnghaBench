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
typedef  int /*<<< orphan*/  uint16_t ;
struct mxc_nand_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_CMD ; 
 int /*<<< orphan*/  NFC_V3_FLASH_CMD ; 
 int /*<<< orphan*/  NFC_V3_LAUNCH ; 
 int /*<<< orphan*/  wait_op_done (struct mxc_nand_host*,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_cmd_v3(struct mxc_nand_host *host, uint16_t cmd, int useirq)
{
	/* fill command */
	writel(cmd, NFC_V3_FLASH_CMD);

	/* send out command */
	writel(NFC_CMD, NFC_V3_LAUNCH);

	/* Wait for operation to complete */
	wait_op_done(host, useirq);
}
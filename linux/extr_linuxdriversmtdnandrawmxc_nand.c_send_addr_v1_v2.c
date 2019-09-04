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
struct mxc_nand_host {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_ADDR ; 
 int /*<<< orphan*/  NFC_V1_V2_CONFIG2 ; 
 int /*<<< orphan*/  NFC_V1_V2_FLASH_ADDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_op_done (struct mxc_nand_host*,int) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_addr_v1_v2(struct mxc_nand_host *host, uint16_t addr, int islast)
{
	dev_dbg(host->dev, "send_addr(host, 0x%x %d)\n", addr, islast);

	writew(addr, NFC_V1_V2_FLASH_ADDR);
	writew(NFC_ADDR, NFC_V1_V2_CONFIG2);

	/* Wait for operation to complete */
	wait_op_done(host, islast);
}
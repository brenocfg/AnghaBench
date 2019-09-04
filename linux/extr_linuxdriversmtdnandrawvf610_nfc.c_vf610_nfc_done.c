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
struct vf610_nfc {int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDLE_EN_BIT ; 
 int /*<<< orphan*/  NFC_FLASH_CMD2 ; 
 int /*<<< orphan*/  NFC_IRQ_STATUS ; 
 int /*<<< orphan*/  START_BIT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  vf610_nfc_clear_status (struct vf610_nfc*) ; 
 int /*<<< orphan*/  vf610_nfc_set (struct vf610_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void vf610_nfc_done(struct vf610_nfc *nfc)
{
	unsigned long timeout = msecs_to_jiffies(100);

	/*
	 * Barrier is needed after this write. This write need
	 * to be done before reading the next register the first
	 * time.
	 * vf610_nfc_set implicates such a barrier by using writel
	 * to write to the register.
	 */
	vf610_nfc_set(nfc, NFC_IRQ_STATUS, IDLE_EN_BIT);
	vf610_nfc_set(nfc, NFC_FLASH_CMD2, START_BIT);

	if (!wait_for_completion_timeout(&nfc->cmd_done, timeout))
		dev_warn(nfc->dev, "Timeout while waiting for BUSY.\n");

	vf610_nfc_clear_status(nfc);
}
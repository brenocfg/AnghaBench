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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ath6kl_device {int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_FW_ASSERT ; 
 int /*<<< orphan*/  COUNT_DEC_ADDRESS ; 
 int /*<<< orphan*/  HIF_RD_SYNC_BYTE_INC ; 
 int /*<<< orphan*/  ath6kl_hif_dump_fw_crash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_read_fwlogs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_recovery_err_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_warn (char*,...) ; 
 int hif_read_write_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_hif_proc_dbg_intr(struct ath6kl_device *dev)
{
	u32 dummy;
	int ret;

	ath6kl_warn("firmware crashed\n");

	/*
	 * read counter to clear the interrupt, the debug error interrupt is
	 * counter 0.
	 */
	ret = hif_read_write_sync(dev->ar, COUNT_DEC_ADDRESS,
				     (u8 *)&dummy, 4, HIF_RD_SYNC_BYTE_INC);
	if (ret)
		ath6kl_warn("Failed to clear debug interrupt: %d\n", ret);

	ath6kl_hif_dump_fw_crash(dev->ar);
	ath6kl_read_fwlogs(dev->ar);
	ath6kl_recovery_err_notify(dev->ar, ATH6KL_FW_ASSERT);

	return ret;
}
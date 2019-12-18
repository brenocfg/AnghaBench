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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBOX_COUNT_DEC_ADDRESS ; 
 int ath10k_sdio_read32 (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 

__attribute__((used)) static int ath10k_sdio_mbox_proc_dbg_intr(struct ath10k *ar)
{
	u32 val;
	int ret;

	/* TODO: Add firmware crash handling */
	ath10k_warn(ar, "firmware crashed\n");

	/* read counter to clear the interrupt, the debug error interrupt is
	 * counter 0.
	 */
	ret = ath10k_sdio_read32(ar, MBOX_COUNT_DEC_ADDRESS, &val);
	if (ret)
		ath10k_warn(ar, "failed to clear debug interrupt: %d\n", ret);

	return ret;
}
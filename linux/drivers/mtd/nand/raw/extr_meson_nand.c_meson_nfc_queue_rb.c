#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int tbers_max; int /*<<< orphan*/  twb; } ;
struct TYPE_3__ {int chip_select; } ;
struct meson_nfc {int /*<<< orphan*/  completion; scalar_t__ reg_base; TYPE_2__ timing; TYPE_1__ param; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FIFO_EMPTY_TIMEOUT ; 
 int NFC_CMD_RB ; 
 int NFC_CMD_RB_INT ; 
 int NFC_RB_IRQ_EN ; 
 scalar_t__ NFC_REG_CFG ; 
 scalar_t__ NFC_REG_CMD ; 
 int /*<<< orphan*/  meson_nfc_cmd_idle (struct meson_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_nfc_drain_cmd (struct meson_nfc*) ; 
 int /*<<< orphan*/  meson_nfc_wait_cmd_finish (struct meson_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int meson_nfc_queue_rb(struct meson_nfc *nfc, int timeout_ms)
{
	u32 cmd, cfg;
	int ret = 0;

	meson_nfc_cmd_idle(nfc, nfc->timing.twb);
	meson_nfc_drain_cmd(nfc);
	meson_nfc_wait_cmd_finish(nfc, CMD_FIFO_EMPTY_TIMEOUT);

	cfg = readl(nfc->reg_base + NFC_REG_CFG);
	cfg |= NFC_RB_IRQ_EN;
	writel(cfg, nfc->reg_base + NFC_REG_CFG);

	reinit_completion(&nfc->completion);

	/* use the max erase time as the maximum clock for waiting R/B */
	cmd = NFC_CMD_RB | NFC_CMD_RB_INT
		| nfc->param.chip_select | nfc->timing.tbers_max;
	writel(cmd, nfc->reg_base + NFC_REG_CMD);

	ret = wait_for_completion_timeout(&nfc->completion,
					  msecs_to_jiffies(timeout_ms));
	if (ret == 0)
		ret = -1;

	return ret;
}
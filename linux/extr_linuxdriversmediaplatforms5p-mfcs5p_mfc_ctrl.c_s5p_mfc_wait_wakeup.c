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
struct s5p_mfc_dev {int risc_on; int /*<<< orphan*/  mfc_cmds; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_MFCV6_PLUS (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  S5P_FIMV_RISC_ON_V6 ; 
 int /*<<< orphan*/  S5P_FIMV_SW_RESET ; 
 int /*<<< orphan*/  S5P_MFC_R2H_CMD_WAKEUP_RET ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int,int /*<<< orphan*/ ) ; 
 int s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*) ; 
 scalar_t__ s5p_mfc_wait_for_done_dev (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_cmd ; 

__attribute__((used)) static int s5p_mfc_wait_wakeup(struct s5p_mfc_dev *dev)
{
	int ret;

	/* Send MFC wakeup command */
	ret = s5p_mfc_hw_call(dev->mfc_cmds, wakeup_cmd, dev);
	if (ret) {
		mfc_err("Failed to send command to MFC - timeout\n");
		return ret;
	}

	/* Release reset signal to the RISC */
	if (IS_MFCV6_PLUS(dev)) {
		dev->risc_on = 1;
		mfc_write(dev, 0x1, S5P_FIMV_RISC_ON_V6);
	} else {
		mfc_write(dev, 0x3ff, S5P_FIMV_SW_RESET);
	}

	if (s5p_mfc_wait_for_done_dev(dev, S5P_MFC_R2H_CMD_WAKEUP_RET)) {
		mfc_err("Failed to wakeup MFC\n");
		return -EIO;
	}
	return ret;
}
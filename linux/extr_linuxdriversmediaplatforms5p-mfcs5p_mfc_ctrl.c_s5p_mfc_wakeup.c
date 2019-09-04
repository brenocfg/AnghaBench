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
struct s5p_mfc_dev {scalar_t__ int_err; scalar_t__ int_type; scalar_t__ int_cond; scalar_t__ risc_on; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_MFCV8_PLUS (struct s5p_mfc_dev*) ; 
 scalar_t__ S5P_MFC_R2H_CMD_WAKEUP_RET ; 
 int /*<<< orphan*/  mfc_debug (int,char*) ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  mfc_err (char*,...) ; 
 int /*<<< orphan*/  s5p_mfc_clean_dev_int_flags (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  s5p_mfc_clear_cmds (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  s5p_mfc_clock_off () ; 
 int /*<<< orphan*/  s5p_mfc_clock_on () ; 
 int /*<<< orphan*/  s5p_mfc_init_memctrl (struct s5p_mfc_dev*) ; 
 int s5p_mfc_reset (struct s5p_mfc_dev*) ; 
 int s5p_mfc_v8_wait_wakeup (struct s5p_mfc_dev*) ; 
 int s5p_mfc_wait_wakeup (struct s5p_mfc_dev*) ; 

int s5p_mfc_wakeup(struct s5p_mfc_dev *dev)
{
	int ret;

	mfc_debug_enter();
	/* 0. MFC reset */
	mfc_debug(2, "MFC reset..\n");
	s5p_mfc_clock_on();
	dev->risc_on = 0;
	ret = s5p_mfc_reset(dev);
	if (ret) {
		mfc_err("Failed to reset MFC - timeout\n");
		s5p_mfc_clock_off();
		return ret;
	}
	mfc_debug(2, "Done MFC reset..\n");
	/* 1. Set DRAM base Addr */
	s5p_mfc_init_memctrl(dev);
	/* 2. Initialize registers of channel I/F */
	s5p_mfc_clear_cmds(dev);
	s5p_mfc_clean_dev_int_flags(dev);
	/* 3. Send MFC wakeup command and wait for completion*/
	if (IS_MFCV8_PLUS(dev))
		ret = s5p_mfc_v8_wait_wakeup(dev);
	else
		ret = s5p_mfc_wait_wakeup(dev);

	s5p_mfc_clock_off();
	if (ret)
		return ret;

	dev->int_cond = 0;
	if (dev->int_err != 0 || dev->int_type !=
						S5P_MFC_R2H_CMD_WAKEUP_RET) {
		/* Failure. */
		mfc_err("Failed to wakeup - error: %d int: %d\n", dev->int_err,
								dev->int_type);
		return -EIO;
	}
	mfc_debug_leave();
	return 0;
}
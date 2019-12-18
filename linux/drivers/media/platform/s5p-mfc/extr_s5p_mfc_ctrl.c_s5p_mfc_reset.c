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
struct s5p_mfc_dev {scalar_t__ risc_on; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_MFCV6_PLUS (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  IS_MFCV7_PLUS (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  MFC_BW_TIMEOUT ; 
 scalar_t__ S5P_FIMV_FW_VERSION_V6 ; 
 scalar_t__ S5P_FIMV_HOST2RISC_CMD_V6 ; 
 int /*<<< orphan*/  S5P_FIMV_MC_STATUS ; 
 scalar_t__ S5P_FIMV_MFC_RESET_V6 ; 
 scalar_t__ S5P_FIMV_REG_CLEAR_BEGIN_V6 ; 
 int S5P_FIMV_REG_CLEAR_COUNT_V6 ; 
 scalar_t__ S5P_FIMV_RISC2HOST_CMD_V6 ; 
 scalar_t__ S5P_FIMV_RISC_ON_V6 ; 
 scalar_t__ S5P_FIMV_SW_RESET ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 unsigned int mfc_read (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int,scalar_t__) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ s5p_mfc_bus_reset (struct s5p_mfc_dev*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int s5p_mfc_reset(struct s5p_mfc_dev *dev)
{
	unsigned int mc_status;
	unsigned long timeout;
	int i;

	mfc_debug_enter();

	if (IS_MFCV6_PLUS(dev)) {
		/* Zero Initialization of MFC registers */
		mfc_write(dev, 0, S5P_FIMV_RISC2HOST_CMD_V6);
		mfc_write(dev, 0, S5P_FIMV_HOST2RISC_CMD_V6);
		mfc_write(dev, 0, S5P_FIMV_FW_VERSION_V6);

		for (i = 0; i < S5P_FIMV_REG_CLEAR_COUNT_V6; i++)
			mfc_write(dev, 0, S5P_FIMV_REG_CLEAR_BEGIN_V6 + (i*4));

		/* check bus reset control before reset */
		if (dev->risc_on)
			if (s5p_mfc_bus_reset(dev))
				return -EIO;
		/* Reset
		 * set RISC_ON to 0 during power_on & wake_up.
		 * V6 needs RISC_ON set to 0 during reset also.
		 */
		if ((!dev->risc_on) || (!IS_MFCV7_PLUS(dev)))
			mfc_write(dev, 0, S5P_FIMV_RISC_ON_V6);

		mfc_write(dev, 0x1FFF, S5P_FIMV_MFC_RESET_V6);
		mfc_write(dev, 0, S5P_FIMV_MFC_RESET_V6);
	} else {
		/* Stop procedure */
		/*  reset RISC */
		mfc_write(dev, 0x3f6, S5P_FIMV_SW_RESET);
		/*  All reset except for MC */
		mfc_write(dev, 0x3e2, S5P_FIMV_SW_RESET);
		mdelay(10);

		timeout = jiffies + msecs_to_jiffies(MFC_BW_TIMEOUT);
		/* Check MC status */
		do {
			if (time_after(jiffies, timeout)) {
				mfc_err("Timeout while resetting MFC\n");
				return -EIO;
			}

			mc_status = mfc_read(dev, S5P_FIMV_MC_STATUS);

		} while (mc_status & 0x3);

		mfc_write(dev, 0x0, S5P_FIMV_SW_RESET);
		mfc_write(dev, 0x3fe, S5P_FIMV_SW_RESET);
	}

	mfc_debug_leave();
	return 0;
}
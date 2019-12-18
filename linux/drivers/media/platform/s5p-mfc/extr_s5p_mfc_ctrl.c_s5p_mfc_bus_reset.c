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
struct s5p_mfc_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MFC_BW_TIMEOUT ; 
 int /*<<< orphan*/  S5P_FIMV_MFC_BUS_RESET_CTRL ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 unsigned int mfc_read (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int s5p_mfc_bus_reset(struct s5p_mfc_dev *dev)
{
	unsigned int status;
	unsigned long timeout;

	/* Reset */
	mfc_write(dev, 0x1, S5P_FIMV_MFC_BUS_RESET_CTRL);
	timeout = jiffies + msecs_to_jiffies(MFC_BW_TIMEOUT);
	/* Check bus status */
	do {
		if (time_after(jiffies, timeout)) {
			mfc_err("Timeout while resetting MFC.\n");
			return -EIO;
		}
		status = mfc_read(dev, S5P_FIMV_MFC_BUS_RESET_CTRL);
	} while ((status & 0x2) == 0);
	return 0;
}
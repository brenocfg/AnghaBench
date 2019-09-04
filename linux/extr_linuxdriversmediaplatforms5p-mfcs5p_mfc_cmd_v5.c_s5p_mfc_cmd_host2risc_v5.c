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
struct s5p_mfc_cmd_args {int* arg; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MFC_BW_TIMEOUT ; 
 int S5P_FIMV_H2R_CMD_EMPTY ; 
 int /*<<< orphan*/  S5P_FIMV_HOST2RISC_ARG1 ; 
 int /*<<< orphan*/  S5P_FIMV_HOST2RISC_ARG2 ; 
 int /*<<< orphan*/  S5P_FIMV_HOST2RISC_ARG3 ; 
 int /*<<< orphan*/  S5P_FIMV_HOST2RISC_ARG4 ; 
 int /*<<< orphan*/  S5P_FIMV_HOST2RISC_CMD ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int mfc_read (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int s5p_mfc_cmd_host2risc_v5(struct s5p_mfc_dev *dev, int cmd,
				struct s5p_mfc_cmd_args *args)
{
	int cur_cmd;
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(MFC_BW_TIMEOUT);
	/* wait until host to risc command register becomes 'H2R_CMD_EMPTY' */
	do {
		if (time_after(jiffies, timeout)) {
			mfc_err("Timeout while waiting for hardware\n");
			return -EIO;
		}
		cur_cmd = mfc_read(dev, S5P_FIMV_HOST2RISC_CMD);
	} while (cur_cmd != S5P_FIMV_H2R_CMD_EMPTY);
	mfc_write(dev, args->arg[0], S5P_FIMV_HOST2RISC_ARG1);
	mfc_write(dev, args->arg[1], S5P_FIMV_HOST2RISC_ARG2);
	mfc_write(dev, args->arg[2], S5P_FIMV_HOST2RISC_ARG3);
	mfc_write(dev, args->arg[3], S5P_FIMV_HOST2RISC_ARG4);
	/* Issue the command */
	mfc_write(dev, cmd, S5P_FIMV_HOST2RISC_CMD);
	return 0;
}
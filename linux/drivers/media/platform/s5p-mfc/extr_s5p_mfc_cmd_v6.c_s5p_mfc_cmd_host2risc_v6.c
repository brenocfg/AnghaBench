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
struct s5p_mfc_cmd_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5P_FIMV_HOST2RISC_CMD_V6 ; 
 int /*<<< orphan*/  S5P_FIMV_HOST2RISC_INT_V6 ; 
 int /*<<< orphan*/  S5P_FIMV_RISC2HOST_CMD_V6 ; 
 int /*<<< orphan*/  mfc_debug (int,char*,int) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_cmd_host2risc_v6(struct s5p_mfc_dev *dev, int cmd,
				struct s5p_mfc_cmd_args *args)
{
	mfc_debug(2, "Issue the command: %d\n", cmd);

	/* Reset RISC2HOST command */
	mfc_write(dev, 0x0, S5P_FIMV_RISC2HOST_CMD_V6);

	/* Issue the command */
	mfc_write(dev, cmd, S5P_FIMV_HOST2RISC_CMD_V6);
	mfc_write(dev, 0x1, S5P_FIMV_HOST2RISC_INT_V6);

	return 0;
}
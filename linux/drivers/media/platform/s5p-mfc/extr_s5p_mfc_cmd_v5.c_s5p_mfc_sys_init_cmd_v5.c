#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct s5p_mfc_dev {TYPE_1__ fw_buf; } ;
struct s5p_mfc_cmd_args {int /*<<< orphan*/ * arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5P_FIMV_H2R_CMD_SYS_INIT ; 
 int /*<<< orphan*/  memset (struct s5p_mfc_cmd_args*,int /*<<< orphan*/ ,int) ; 
 int s5p_mfc_cmd_host2risc_v5 (struct s5p_mfc_dev*,int /*<<< orphan*/ ,struct s5p_mfc_cmd_args*) ; 

__attribute__((used)) static int s5p_mfc_sys_init_cmd_v5(struct s5p_mfc_dev *dev)
{
	struct s5p_mfc_cmd_args h2r_args;

	memset(&h2r_args, 0, sizeof(struct s5p_mfc_cmd_args));
	h2r_args.arg[0] = dev->fw_buf.size;
	return s5p_mfc_cmd_host2risc_v5(dev, S5P_FIMV_H2R_CMD_SYS_INIT,
			&h2r_args);
}
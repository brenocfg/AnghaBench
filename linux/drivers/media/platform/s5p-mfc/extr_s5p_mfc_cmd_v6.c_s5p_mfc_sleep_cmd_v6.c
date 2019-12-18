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
 int /*<<< orphan*/  S5P_FIMV_H2R_CMD_SLEEP_V6 ; 
 int /*<<< orphan*/  memset (struct s5p_mfc_cmd_args*,int /*<<< orphan*/ ,int) ; 
 int s5p_mfc_cmd_host2risc_v6 (struct s5p_mfc_dev*,int /*<<< orphan*/ ,struct s5p_mfc_cmd_args*) ; 

__attribute__((used)) static int s5p_mfc_sleep_cmd_v6(struct s5p_mfc_dev *dev)
{
	struct s5p_mfc_cmd_args h2r_args;

	memset(&h2r_args, 0, sizeof(struct s5p_mfc_cmd_args));
	return s5p_mfc_cmd_host2risc_v6(dev, S5P_FIMV_H2R_CMD_SLEEP_V6,
			&h2r_args);
}
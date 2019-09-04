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
struct s5p_mfc_dev {int /*<<< orphan*/  curr_ctx; } ;
struct s5p_mfc_ctx {scalar_t__ state; int /*<<< orphan*/  inst_no; int /*<<< orphan*/  num; struct s5p_mfc_dev* dev; } ;
struct s5p_mfc_cmd_args {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MFCINST_FREE ; 
 int /*<<< orphan*/  S5P_FIMV_H2R_CMD_CLOSE_INSTANCE_V6 ; 
 int /*<<< orphan*/  S5P_FIMV_INSTANCE_ID_V6 ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s5p_mfc_cmd_host2risc_v6 (struct s5p_mfc_dev*,int /*<<< orphan*/ ,struct s5p_mfc_cmd_args*) ; 

__attribute__((used)) static int s5p_mfc_close_inst_cmd_v6(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_cmd_args h2r_args;
	int ret = 0;

	dev->curr_ctx = ctx->num;
	if (ctx->state != MFCINST_FREE) {
		mfc_write(dev, ctx->inst_no, S5P_FIMV_INSTANCE_ID_V6);
		ret = s5p_mfc_cmd_host2risc_v6(dev,
					S5P_FIMV_H2R_CMD_CLOSE_INSTANCE_V6,
					&h2r_args);
	} else {
		ret = -EINVAL;
	}

	return ret;
}
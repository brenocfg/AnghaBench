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
struct s5p_mfc_cmd_args {int /*<<< orphan*/ * arg; } ;

/* Variables and functions */
 int EINVAL ; 
 void* MFCINST_ERROR ; 
 scalar_t__ MFCINST_FREE ; 
 int /*<<< orphan*/  S5P_FIMV_H2R_CMD_CLOSE_INSTANCE ; 
 int /*<<< orphan*/  memset (struct s5p_mfc_cmd_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int s5p_mfc_cmd_host2risc_v5 (struct s5p_mfc_dev*,int /*<<< orphan*/ ,struct s5p_mfc_cmd_args*) ; 

__attribute__((used)) static int s5p_mfc_close_inst_cmd_v5(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_cmd_args h2r_args;
	int ret;

	if (ctx->state == MFCINST_FREE) {
		mfc_err("Instance already returned\n");
		ctx->state = MFCINST_ERROR;
		return -EINVAL;
	}
	/* Closing decoding instance  */
	mfc_debug(2, "Returning instance number %d\n", ctx->inst_no);
	dev->curr_ctx = ctx->num;
	memset(&h2r_args, 0, sizeof(struct s5p_mfc_cmd_args));
	h2r_args.arg[0] = ctx->inst_no;
	ret = s5p_mfc_cmd_host2risc_v5(dev, S5P_FIMV_H2R_CMD_CLOSE_INSTANCE,
								&h2r_args);
	if (ret) {
		mfc_err("Failed to return an instance\n");
		ctx->state = MFCINST_ERROR;
		return -EINVAL;
	}
	return 0;
}
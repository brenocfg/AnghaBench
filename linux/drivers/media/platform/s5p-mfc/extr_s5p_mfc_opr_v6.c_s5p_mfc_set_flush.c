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
struct s5p_mfc_regs {int /*<<< orphan*/  instance_id; } ;
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_cmds; int /*<<< orphan*/  curr_ctx; struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {int /*<<< orphan*/  inst_no; int /*<<< orphan*/  num; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5P_FIMV_H2R_CMD_FLUSH_V6 ; 
 int /*<<< orphan*/  cmd_host2risc ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void s5p_mfc_set_flush(struct s5p_mfc_ctx *ctx, int flush)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	if (flush) {
		dev->curr_ctx = ctx->num;
		writel(ctx->inst_no, mfc_regs->instance_id);
		s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
				S5P_FIMV_H2R_CMD_FLUSH_V6, NULL);
	}
}
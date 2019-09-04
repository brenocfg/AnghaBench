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
struct s5p_mfc_regs {scalar_t__ e_h264_aso_slice_order_0; } ;
struct s5p_mfc_h264_enc_params {int /*<<< orphan*/ * aso_slice_order; scalar_t__ aso; } ;
struct TYPE_2__ {struct s5p_mfc_h264_enc_params h264; } ;
struct s5p_mfc_enc_params {TYPE_1__ codec; } ;
struct s5p_mfc_dev {struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {struct s5p_mfc_enc_params enc_params; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s5p_mfc_h264_set_aso_slice_order_v6(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	struct s5p_mfc_h264_enc_params *p_h264 = &p->codec.h264;
	int i;

	if (p_h264->aso) {
		for (i = 0; i < ARRAY_SIZE(p_h264->aso_slice_order); i++) {
			writel(p_h264->aso_slice_order[i],
				mfc_regs->e_h264_aso_slice_order_0 + i * 4);
		}
	}
	return 0;
}
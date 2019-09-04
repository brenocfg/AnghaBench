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
struct s5p_mfc_ctx {struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 unsigned int S5P_FIMV_DPB_FLUSH_MASK ; 
 unsigned int S5P_FIMV_DPB_FLUSH_SHIFT ; 
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_DPB_CONF_CTRL ; 
 unsigned int mfc_read (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_mfc_set_flush(struct s5p_mfc_ctx *ctx, int flush)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned int dpb;

	if (flush)
		dpb = mfc_read(dev, S5P_FIMV_SI_CH0_DPB_CONF_CTRL) | (
			S5P_FIMV_DPB_FLUSH_MASK << S5P_FIMV_DPB_FLUSH_SHIFT);
	else
		dpb = mfc_read(dev, S5P_FIMV_SI_CH0_DPB_CONF_CTRL) &
			~(S5P_FIMV_DPB_FLUSH_MASK << S5P_FIMV_DPB_FLUSH_SHIFT);
	mfc_write(dev, dpb, S5P_FIMV_SI_CH0_DPB_CONF_CTRL);
}
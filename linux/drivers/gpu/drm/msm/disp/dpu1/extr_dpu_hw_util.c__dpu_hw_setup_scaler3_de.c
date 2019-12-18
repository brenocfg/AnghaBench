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
typedef  int u32 ;
struct dpu_hw_scaler3_de_cfg {int sharpen_level1; int sharpen_level2; int limit; int prec_shift; int clip; int thr_quiet; int thr_dieout; int thr_low; int thr_high; int* adjust_a; int* adjust_b; int* adjust_c; int /*<<< orphan*/  enable; } ;
struct dpu_hw_blk_reg_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int,int) ; 
 int QSEED3_DE_ADJUST_DATA_0 ; 
 int QSEED3_DE_ADJUST_DATA_1 ; 
 int QSEED3_DE_ADJUST_DATA_2 ; 
 int QSEED3_DE_SHAPE_CTL ; 
 int QSEED3_DE_SHARPEN ; 
 int QSEED3_DE_SHARPEN_CTL ; 
 int QSEED3_DE_THRESHOLD ; 

__attribute__((used)) static void _dpu_hw_setup_scaler3_de(struct dpu_hw_blk_reg_map *c,
		struct dpu_hw_scaler3_de_cfg *de_cfg, u32 offset)
{
	u32 sharp_lvl, sharp_ctl, shape_ctl, de_thr;
	u32 adjust_a, adjust_b, adjust_c;

	if (!de_cfg->enable)
		return;

	sharp_lvl = (de_cfg->sharpen_level1 & 0x1FF) |
		((de_cfg->sharpen_level2 & 0x1FF) << 16);

	sharp_ctl = ((de_cfg->limit & 0xF) << 9) |
		((de_cfg->prec_shift & 0x7) << 13) |
		((de_cfg->clip & 0x7) << 16);

	shape_ctl = (de_cfg->thr_quiet & 0xFF) |
		((de_cfg->thr_dieout & 0x3FF) << 16);

	de_thr = (de_cfg->thr_low & 0x3FF) |
		((de_cfg->thr_high & 0x3FF) << 16);

	adjust_a = (de_cfg->adjust_a[0] & 0x3FF) |
		((de_cfg->adjust_a[1] & 0x3FF) << 10) |
		((de_cfg->adjust_a[2] & 0x3FF) << 20);

	adjust_b = (de_cfg->adjust_b[0] & 0x3FF) |
		((de_cfg->adjust_b[1] & 0x3FF) << 10) |
		((de_cfg->adjust_b[2] & 0x3FF) << 20);

	adjust_c = (de_cfg->adjust_c[0] & 0x3FF) |
		((de_cfg->adjust_c[1] & 0x3FF) << 10) |
		((de_cfg->adjust_c[2] & 0x3FF) << 20);

	DPU_REG_WRITE(c, QSEED3_DE_SHARPEN + offset, sharp_lvl);
	DPU_REG_WRITE(c, QSEED3_DE_SHARPEN_CTL + offset, sharp_ctl);
	DPU_REG_WRITE(c, QSEED3_DE_SHAPE_CTL + offset, shape_ctl);
	DPU_REG_WRITE(c, QSEED3_DE_THRESHOLD + offset, de_thr);
	DPU_REG_WRITE(c, QSEED3_DE_ADJUST_DATA_0 + offset, adjust_a);
	DPU_REG_WRITE(c, QSEED3_DE_ADJUST_DATA_1 + offset, adjust_b);
	DPU_REG_WRITE(c, QSEED3_DE_ADJUST_DATA_2 + offset, adjust_c);

}
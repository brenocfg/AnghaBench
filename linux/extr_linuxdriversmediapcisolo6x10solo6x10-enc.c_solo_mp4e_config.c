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
struct solo_dev {scalar_t__ type; int nr_chans; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int SOLO_COMP_ATTR_FCODE (int) ; 
 int SOLO_COMP_TIME_INC (int /*<<< orphan*/ ) ; 
 int SOLO_COMP_TIME_WIDTH (int) ; 
 int SOLO_DCT_INTERVAL (int) ; 
 scalar_t__ SOLO_DEV_6010 ; 
 scalar_t__ SOLO_DEV_6110 ; 
 int SOLO_EREF_EXT_ADDR (struct solo_dev*) ; 
 int SOLO_EREF_EXT_SIZE ; 
 int SOLO_JPEG_EXT_SIZE (struct solo_dev*) ; 
 int SOLO_MP4E_EXT_ADDR (struct solo_dev*) ; 
 int SOLO_MP4E_EXT_SIZE (struct solo_dev*) ; 
 int /*<<< orphan*/  SOLO_VE_ATTR ; 
 int SOLO_VE_BLOCK_BASE (int) ; 
 int SOLO_VE_BLOCK_SIZE (int) ; 
 int SOLO_VE_BYTE_ALIGN (int) ; 
 int /*<<< orphan*/  SOLO_VE_CFG0 ; 
 int /*<<< orphan*/  SOLO_VE_CFG1 ; 
 int /*<<< orphan*/  SOLO_VE_CH_MOT (int) ; 
 int /*<<< orphan*/  SOLO_VE_CH_REF_BASE (int) ; 
 int /*<<< orphan*/  SOLO_VE_CH_REF_BASE_E (int) ; 
 int /*<<< orphan*/  SOLO_VE_COMPT_MOT ; 
 int /*<<< orphan*/  SOLO_VE_ENCRYP_INIT ; 
 int /*<<< orphan*/  SOLO_VE_ENCRYP_POLY ; 
 int SOLO_VE_INSERT_INDEX ; 
 int SOLO_VE_INTR_CTRL (int /*<<< orphan*/ ) ; 
 int SOLO_VE_JPEG_SIZE_H (int) ; 
 int SOLO_VE_LITTLE_ENDIAN ; 
 int SOLO_VE_MOTION_MODE (int /*<<< orphan*/ ) ; 
 int SOLO_VE_MPEG_SIZE_H (int) ; 
 int /*<<< orphan*/  SOLO_VE_VMRK_INIT_KEY ; 
 int /*<<< orphan*/  SOLO_VE_WMRK_ENABLE ; 
 int /*<<< orphan*/  SOLO_VE_WMRK_POLY ; 
 int /*<<< orphan*/  SOLO_VE_WMRK_STRL ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void solo_mp4e_config(struct solo_dev *solo_dev)
{
	int i;
	u32 cfg;

	solo_reg_write(solo_dev, SOLO_VE_CFG0,
		       SOLO_VE_INTR_CTRL(IRQ_LEVEL) |
		       SOLO_VE_BLOCK_SIZE(SOLO_MP4E_EXT_SIZE(solo_dev) >> 16) |
		       SOLO_VE_BLOCK_BASE(SOLO_MP4E_EXT_ADDR(solo_dev) >> 16));


	cfg = SOLO_VE_BYTE_ALIGN(2) | SOLO_VE_INSERT_INDEX
		| SOLO_VE_MOTION_MODE(0);
	if (solo_dev->type != SOLO_DEV_6010) {
		cfg |= SOLO_VE_MPEG_SIZE_H(
			(SOLO_MP4E_EXT_SIZE(solo_dev) >> 24) & 0x0f);
		cfg |= SOLO_VE_JPEG_SIZE_H(
			(SOLO_JPEG_EXT_SIZE(solo_dev) >> 24) & 0x0f);
	}
	solo_reg_write(solo_dev, SOLO_VE_CFG1, cfg);

	solo_reg_write(solo_dev, SOLO_VE_WMRK_POLY, 0);
	solo_reg_write(solo_dev, SOLO_VE_VMRK_INIT_KEY, 0);
	solo_reg_write(solo_dev, SOLO_VE_WMRK_STRL, 0);
	if (solo_dev->type == SOLO_DEV_6110)
		solo_reg_write(solo_dev, SOLO_VE_WMRK_ENABLE, 0);
	solo_reg_write(solo_dev, SOLO_VE_ENCRYP_POLY, 0);
	solo_reg_write(solo_dev, SOLO_VE_ENCRYP_INIT, 0);

	solo_reg_write(solo_dev, SOLO_VE_ATTR,
		       SOLO_VE_LITTLE_ENDIAN |
		       SOLO_COMP_ATTR_FCODE(1) |
		       SOLO_COMP_TIME_INC(0) |
		       SOLO_COMP_TIME_WIDTH(15) |
		       SOLO_DCT_INTERVAL(solo_dev->type == SOLO_DEV_6010 ? 9 : 10));

	for (i = 0; i < solo_dev->nr_chans; i++) {
		solo_reg_write(solo_dev, SOLO_VE_CH_REF_BASE(i),
			       (SOLO_EREF_EXT_ADDR(solo_dev) +
			       (i * SOLO_EREF_EXT_SIZE)) >> 16);
		solo_reg_write(solo_dev, SOLO_VE_CH_REF_BASE_E(i),
			       (SOLO_EREF_EXT_ADDR(solo_dev) +
			       ((i + 16) * SOLO_EREF_EXT_SIZE)) >> 16);
	}

	if (solo_dev->type == SOLO_DEV_6110) {
		solo_reg_write(solo_dev, SOLO_VE_COMPT_MOT, 0x00040008);
	} else {
		for (i = 0; i < solo_dev->nr_chans; i++)
			solo_reg_write(solo_dev, SOLO_VE_CH_MOT(i), 0x100);
	}
}
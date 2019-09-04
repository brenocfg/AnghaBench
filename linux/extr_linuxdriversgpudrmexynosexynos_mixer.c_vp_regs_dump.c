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
typedef  int /*<<< orphan*/  u32 ;
struct mixer_context {scalar_t__ vp_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ VP_BOT_C_PTR ; 
 scalar_t__ VP_BOT_Y_PTR ; 
 scalar_t__ VP_DST_HEIGHT ; 
 scalar_t__ VP_DST_H_POSITION ; 
 scalar_t__ VP_DST_V_POSITION ; 
 scalar_t__ VP_DST_WIDTH ; 
 scalar_t__ VP_ENABLE ; 
 scalar_t__ VP_ENDIAN_MODE ; 
 scalar_t__ VP_FIELD_ID ; 
 scalar_t__ VP_H_RATIO ; 
 scalar_t__ VP_IMG_SIZE_C ; 
 scalar_t__ VP_IMG_SIZE_Y ; 
 scalar_t__ VP_MODE ; 
 scalar_t__ VP_PER_RATE_CTRL ; 
 scalar_t__ VP_SHADOW_UPDATE ; 
 scalar_t__ VP_SRC_HEIGHT ; 
 scalar_t__ VP_SRC_H_POSITION ; 
 scalar_t__ VP_SRC_V_POSITION ; 
 scalar_t__ VP_SRC_WIDTH ; 
 scalar_t__ VP_SRESET ; 
 scalar_t__ VP_TOP_C_PTR ; 
 scalar_t__ VP_TOP_Y_PTR ; 
 scalar_t__ VP_V_RATIO ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static void vp_regs_dump(struct mixer_context *ctx)
{
#define DUMPREG(reg_id) \
do { \
	DRM_DEBUG_KMS(#reg_id " = %08x\n", \
		(u32) readl(ctx->vp_regs + reg_id)); \
} while (0)

	DUMPREG(VP_ENABLE);
	DUMPREG(VP_SRESET);
	DUMPREG(VP_SHADOW_UPDATE);
	DUMPREG(VP_FIELD_ID);
	DUMPREG(VP_MODE);
	DUMPREG(VP_IMG_SIZE_Y);
	DUMPREG(VP_IMG_SIZE_C);
	DUMPREG(VP_PER_RATE_CTRL);
	DUMPREG(VP_TOP_Y_PTR);
	DUMPREG(VP_BOT_Y_PTR);
	DUMPREG(VP_TOP_C_PTR);
	DUMPREG(VP_BOT_C_PTR);
	DUMPREG(VP_ENDIAN_MODE);
	DUMPREG(VP_SRC_H_POSITION);
	DUMPREG(VP_SRC_V_POSITION);
	DUMPREG(VP_SRC_WIDTH);
	DUMPREG(VP_SRC_HEIGHT);
	DUMPREG(VP_DST_H_POSITION);
	DUMPREG(VP_DST_V_POSITION);
	DUMPREG(VP_DST_WIDTH);
	DUMPREG(VP_DST_HEIGHT);
	DUMPREG(VP_H_RATIO);
	DUMPREG(VP_V_RATIO);

#undef DUMPREG
}
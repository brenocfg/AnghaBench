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
struct mixer_context {scalar_t__ mixer_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MXR_CFG ; 
 scalar_t__ MXR_GRAPHIC0_BASE ; 
 scalar_t__ MXR_GRAPHIC0_CFG ; 
 scalar_t__ MXR_GRAPHIC0_DXY ; 
 scalar_t__ MXR_GRAPHIC0_SPAN ; 
 scalar_t__ MXR_GRAPHIC0_SXY ; 
 scalar_t__ MXR_GRAPHIC0_WH ; 
 scalar_t__ MXR_GRAPHIC1_BASE ; 
 scalar_t__ MXR_GRAPHIC1_CFG ; 
 scalar_t__ MXR_GRAPHIC1_DXY ; 
 scalar_t__ MXR_GRAPHIC1_SPAN ; 
 scalar_t__ MXR_GRAPHIC1_SXY ; 
 scalar_t__ MXR_GRAPHIC1_WH ; 
 scalar_t__ MXR_INT_EN ; 
 scalar_t__ MXR_INT_STATUS ; 
 scalar_t__ MXR_LAYER_CFG ; 
 scalar_t__ MXR_STATUS ; 
 scalar_t__ MXR_VIDEO_CFG ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static void mixer_regs_dump(struct mixer_context *ctx)
{
#define DUMPREG(reg_id) \
do { \
	DRM_DEBUG_KMS(#reg_id " = %08x\n", \
		(u32)readl(ctx->mixer_regs + reg_id)); \
} while (0)

	DUMPREG(MXR_STATUS);
	DUMPREG(MXR_CFG);
	DUMPREG(MXR_INT_EN);
	DUMPREG(MXR_INT_STATUS);

	DUMPREG(MXR_LAYER_CFG);
	DUMPREG(MXR_VIDEO_CFG);

	DUMPREG(MXR_GRAPHIC0_CFG);
	DUMPREG(MXR_GRAPHIC0_BASE);
	DUMPREG(MXR_GRAPHIC0_SPAN);
	DUMPREG(MXR_GRAPHIC0_WH);
	DUMPREG(MXR_GRAPHIC0_SXY);
	DUMPREG(MXR_GRAPHIC0_DXY);

	DUMPREG(MXR_GRAPHIC1_CFG);
	DUMPREG(MXR_GRAPHIC1_BASE);
	DUMPREG(MXR_GRAPHIC1_SPAN);
	DUMPREG(MXR_GRAPHIC1_WH);
	DUMPREG(MXR_GRAPHIC1_SXY);
	DUMPREG(MXR_GRAPHIC1_DXY);
#undef DUMPREG
}
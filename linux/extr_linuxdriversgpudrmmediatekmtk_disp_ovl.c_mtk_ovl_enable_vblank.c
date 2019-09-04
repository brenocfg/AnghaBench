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
struct mtk_disp_ovl {struct drm_crtc* crtc; } ;
struct mtk_ddp_comp {scalar_t__ regs; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 scalar_t__ DISP_REG_OVL_INTEN ; 
 scalar_t__ DISP_REG_OVL_INTSTA ; 
 int /*<<< orphan*/  OVL_FME_CPL_INT ; 
 struct mtk_disp_ovl* comp_to_ovl (struct mtk_ddp_comp*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_ovl_enable_vblank(struct mtk_ddp_comp *comp,
				  struct drm_crtc *crtc)
{
	struct mtk_disp_ovl *ovl = comp_to_ovl(comp);

	ovl->crtc = crtc;
	writel(0x0, comp->regs + DISP_REG_OVL_INTSTA);
	writel_relaxed(OVL_FME_CPL_INT, comp->regs + DISP_REG_OVL_INTEN);
}
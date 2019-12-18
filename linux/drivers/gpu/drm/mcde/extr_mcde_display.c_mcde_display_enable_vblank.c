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
struct mcde {scalar_t__ regs; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_simple_display_pipe {struct drm_crtc crtc; } ;
struct drm_device {struct mcde* dev_private; } ;

/* Variables and functions */
 scalar_t__ MCDE_IMSCPP ; 
 int MCDE_PP_VCMPA ; 
 int MCDE_PP_VCMPB ; 
 int MCDE_PP_VCMPC0 ; 
 int MCDE_PP_VCMPC1 ; 
 int MCDE_PP_VSCC0 ; 
 int MCDE_PP_VSCC1 ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mcde_display_enable_vblank(struct drm_simple_display_pipe *pipe)
{
	struct drm_crtc *crtc = &pipe->crtc;
	struct drm_device *drm = crtc->dev;
	struct mcde *mcde = drm->dev_private;
	u32 val;

	/* Enable all VBLANK IRQs */
	val = MCDE_PP_VCMPA |
		MCDE_PP_VCMPB |
		MCDE_PP_VSCC0 |
		MCDE_PP_VSCC1 |
		MCDE_PP_VCMPC0 |
		MCDE_PP_VCMPC1;
	writel(val, mcde->regs + MCDE_IMSCPP);

	return 0;
}
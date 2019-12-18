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
struct hibmc_drm_private {scalar_t__ mmio; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct hibmc_drm_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ HIBMC_CURRENT_GATE ; 
 unsigned int HIBMC_CURR_GATE_DISPLAY (int /*<<< orphan*/ ) ; 
 unsigned int HIBMC_CURR_GATE_DISPLAY_MASK ; 
 unsigned int HIBMC_CURR_GATE_LOCALMEM (int /*<<< orphan*/ ) ; 
 unsigned int HIBMC_CURR_GATE_LOCALMEM_MASK ; 
 int /*<<< orphan*/  HIBMC_PW_MODE_CTL_MODE_SLEEP ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  hibmc_set_current_gate (struct hibmc_drm_private*,unsigned int) ; 
 int /*<<< orphan*/  hibmc_set_power_mode (struct hibmc_drm_private*,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static void hibmc_crtc_atomic_disable(struct drm_crtc *crtc,
				      struct drm_crtc_state *old_state)
{
	unsigned int reg;
	struct hibmc_drm_private *priv = crtc->dev->dev_private;

	drm_crtc_vblank_off(crtc);

	hibmc_set_power_mode(priv, HIBMC_PW_MODE_CTL_MODE_SLEEP);

	/* Enable display power gate & LOCALMEM power gate*/
	reg = readl(priv->mmio + HIBMC_CURRENT_GATE);
	reg &= ~HIBMC_CURR_GATE_LOCALMEM_MASK;
	reg &= ~HIBMC_CURR_GATE_DISPLAY_MASK;
	reg |= HIBMC_CURR_GATE_LOCALMEM(0);
	reg |= HIBMC_CURR_GATE_DISPLAY(0);
	hibmc_set_current_gate(priv, reg);
}
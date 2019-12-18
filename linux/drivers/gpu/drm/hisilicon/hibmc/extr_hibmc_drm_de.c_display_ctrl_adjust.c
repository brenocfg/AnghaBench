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
typedef  unsigned int u32 ;
struct hibmc_drm_private {scalar_t__ mmio; } ;
struct drm_display_mode {unsigned long hdisplay; unsigned long vdisplay; } ;
struct drm_device {struct hibmc_drm_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ CRT_PLL2_HS ; 
 int /*<<< orphan*/  HIBMC_CRTSELECT_CRT ; 
 scalar_t__ HIBMC_CRT_AUTO_CENTERING_BR ; 
 int /*<<< orphan*/  HIBMC_CRT_AUTO_CENTERING_BR_BOTTOM ; 
 int /*<<< orphan*/  HIBMC_CRT_AUTO_CENTERING_BR_RIGHT ; 
 scalar_t__ HIBMC_CRT_AUTO_CENTERING_TL ; 
 int /*<<< orphan*/  HIBMC_CRT_AUTO_CENTERING_TL_LEFT ; 
 int /*<<< orphan*/  HIBMC_CRT_AUTO_CENTERING_TL_TOP ; 
 scalar_t__ HIBMC_CRT_DISP_CTL ; 
 unsigned int HIBMC_CRT_DISP_CTL_CLOCK_PHASE (int /*<<< orphan*/ ) ; 
 unsigned int HIBMC_CRT_DISP_CTL_CLOCK_PHASE_MASK ; 
 unsigned int HIBMC_CRT_DISP_CTL_CRTSELECT (int /*<<< orphan*/ ) ; 
 unsigned int HIBMC_CRT_DISP_CTL_CRTSELECT_MASK ; 
 unsigned int HIBMC_FIELD (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  get_pll_config (unsigned long,unsigned long,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  set_vclock_hisilicon (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static unsigned int display_ctrl_adjust(struct drm_device *dev,
					struct drm_display_mode *mode,
					unsigned int ctrl)
{
	unsigned long x, y;
	u32 pll1; /* bit[31:0] of PLL */
	u32 pll2; /* bit[63:32] of PLL */
	struct hibmc_drm_private *priv = dev->dev_private;

	x = mode->hdisplay;
	y = mode->vdisplay;

	get_pll_config(x, y, &pll1, &pll2);
	writel(pll2, priv->mmio + CRT_PLL2_HS);
	set_vclock_hisilicon(dev, pll1);

	/*
	 * Hisilicon has to set up the top-left and bottom-right
	 * registers as well.
	 * Note that normal chip only use those two register for
	 * auto-centering mode.
	 */
	writel(HIBMC_FIELD(HIBMC_CRT_AUTO_CENTERING_TL_TOP, 0) |
	       HIBMC_FIELD(HIBMC_CRT_AUTO_CENTERING_TL_LEFT, 0),
	       priv->mmio + HIBMC_CRT_AUTO_CENTERING_TL);

	writel(HIBMC_FIELD(HIBMC_CRT_AUTO_CENTERING_BR_BOTTOM, y - 1) |
	       HIBMC_FIELD(HIBMC_CRT_AUTO_CENTERING_BR_RIGHT, x - 1),
	       priv->mmio + HIBMC_CRT_AUTO_CENTERING_BR);

	/*
	 * Assume common fields in ctrl have been properly set before
	 * calling this function.
	 * This function only sets the extra fields in ctrl.
	 */

	/* Set bit 25 of display controller: Select CRT or VGA clock */
	ctrl &= ~HIBMC_CRT_DISP_CTL_CRTSELECT_MASK;
	ctrl &= ~HIBMC_CRT_DISP_CTL_CLOCK_PHASE_MASK;

	ctrl |= HIBMC_CRT_DISP_CTL_CRTSELECT(HIBMC_CRTSELECT_CRT);

	/* clock_phase_polarity is 0 */
	ctrl |= HIBMC_CRT_DISP_CTL_CLOCK_PHASE(0);

	writel(ctrl, priv->mmio + HIBMC_CRT_DISP_CTL);

	return ctrl;
}
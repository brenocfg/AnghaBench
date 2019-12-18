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
struct ltdc_device {int /*<<< orphan*/  regs; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; struct ltdc_device* dev_private; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int AWCR_AAH ; 
 int BPCR_AVBP ; 
 int CPSR_CYPOS ; 
 int /*<<< orphan*/  LTDC_AWCR ; 
 int /*<<< orphan*/  LTDC_BPCR ; 
 int /*<<< orphan*/  LTDC_CPSR ; 
 int /*<<< orphan*/  LTDC_TWCR ; 
 int TWCR_TOTALH ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ pm_runtime_active (int /*<<< orphan*/ ) ; 
 int reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool ltdc_crtc_scanoutpos(struct drm_device *ddev, unsigned int pipe,
			  bool in_vblank_irq, int *vpos, int *hpos,
			  ktime_t *stime, ktime_t *etime,
			  const struct drm_display_mode *mode)
{
	struct ltdc_device *ldev = ddev->dev_private;
	int line, vactive_start, vactive_end, vtotal;

	if (stime)
		*stime = ktime_get();

	/* The active area starts after vsync + front porch and ends
	 * at vsync + front porc + display size.
	 * The total height also include back porch.
	 * We have 3 possible cases to handle:
	 * - line < vactive_start: vpos = line - vactive_start and will be
	 * negative
	 * - vactive_start < line < vactive_end: vpos = line - vactive_start
	 * and will be positive
	 * - line > vactive_end: vpos = line - vtotal - vactive_start
	 * and will negative
	 *
	 * Computation for the two first cases are identical so we can
	 * simplify the code and only test if line > vactive_end
	 */
	if (pm_runtime_active(ddev->dev)) {
		line = reg_read(ldev->regs, LTDC_CPSR) & CPSR_CYPOS;
		vactive_start = reg_read(ldev->regs, LTDC_BPCR) & BPCR_AVBP;
		vactive_end = reg_read(ldev->regs, LTDC_AWCR) & AWCR_AAH;
		vtotal = reg_read(ldev->regs, LTDC_TWCR) & TWCR_TOTALH;

		if (line > vactive_end)
			*vpos = line - vtotal - vactive_start;
		else
			*vpos = line - vactive_start;
	} else {
		*vpos = 0;
	}

	*hpos = 0;

	if (etime)
		*etime = ktime_get();

	return true;
}
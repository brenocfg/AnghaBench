#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct malidp_irq_map {int irq_mask; int err_mask; int vsync_irq; } ;
struct malidp_hw_device {int mw_state; scalar_t__ pm_suspended; struct malidp_hw* hw; } ;
struct TYPE_3__ {int vsync_irq; } ;
struct TYPE_4__ {TYPE_1__ dc_irq_map; scalar_t__ dc_base; scalar_t__ se_base; struct malidp_irq_map se_irq_map; } ;
struct malidp_hw {int /*<<< orphan*/  (* set_config_valid ) (struct malidp_hw_device*,int) ;TYPE_2__ map; int /*<<< orphan*/  (* disable_memwrite ) (struct malidp_hw_device*) ;} ;
struct malidp_drm {int /*<<< orphan*/  config_valid; int /*<<< orphan*/  mw_connector; int /*<<< orphan*/  crtc; int /*<<< orphan*/  se_errors; struct malidp_hw_device* dev; } ;
struct drm_device {struct malidp_drm* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MALIDP_CONFIG_START ; 
 scalar_t__ MALIDP_REG_MASKIRQ ; 
 scalar_t__ MALIDP_REG_STATUS ; 
 int /*<<< orphan*/  MALIDP_SE_BLOCK ; 
 int MW_NOT_ENABLED ; 
#define  MW_ONESHOT 131 
#define  MW_RESTART 130 
#define  MW_START 129 
#define  MW_STOP 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_writeback_signal_completion (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_error (struct malidp_drm*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_clear_irq (struct malidp_hw_device*,int /*<<< orphan*/ ,int) ; 
 int malidp_hw_read (struct malidp_hw_device*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct malidp_hw_device*) ; 
 int /*<<< orphan*/  stub2 (struct malidp_hw_device*,int) ; 

__attribute__((used)) static irqreturn_t malidp_se_irq(int irq, void *arg)
{
	struct drm_device *drm = arg;
	struct malidp_drm *malidp = drm->dev_private;
	struct malidp_hw_device *hwdev = malidp->dev;
	struct malidp_hw *hw = hwdev->hw;
	const struct malidp_irq_map *se = &hw->map.se_irq_map;
	u32 status, mask;

	/*
	 * if we are suspended it is likely that we were invoked because
	 * we share an interrupt line with some other driver, don't try
	 * to read the hardware registers
	 */
	if (hwdev->pm_suspended)
		return IRQ_NONE;

	status = malidp_hw_read(hwdev, hw->map.se_base + MALIDP_REG_STATUS);
	if (!(status & (se->irq_mask | se->err_mask)))
		return IRQ_NONE;

#ifdef CONFIG_DEBUG_FS
	if (status & se->err_mask)
		malidp_error(malidp, &malidp->se_errors, status,
			     drm_crtc_vblank_count(&malidp->crtc));
#endif
	mask = malidp_hw_read(hwdev, hw->map.se_base + MALIDP_REG_MASKIRQ);
	status &= mask;

	if (status & se->vsync_irq) {
		switch (hwdev->mw_state) {
		case MW_ONESHOT:
			drm_writeback_signal_completion(&malidp->mw_connector, 0);
			break;
		case MW_STOP:
			drm_writeback_signal_completion(&malidp->mw_connector, 0);
			/* disable writeback after stop */
			hwdev->mw_state = MW_NOT_ENABLED;
			break;
		case MW_RESTART:
			drm_writeback_signal_completion(&malidp->mw_connector, 0);
			/* fall through - to a new start */
		case MW_START:
			/* writeback started, need to emulate one-shot mode */
			hw->disable_memwrite(hwdev);
			/*
			 * only set config_valid HW bit if there is no other update
			 * in progress or if we raced ahead of the DE IRQ handler
			 * and config_valid flag will not be update until later
			 */
			status = malidp_hw_read(hwdev, hw->map.dc_base + MALIDP_REG_STATUS);
			if ((atomic_read(&malidp->config_valid) != MALIDP_CONFIG_START) ||
			    (status & hw->map.dc_irq_map.vsync_irq))
				hw->set_config_valid(hwdev, 1);
			break;
		}
	}

	malidp_hw_clear_irq(hwdev, MALIDP_SE_BLOCK, status);

	return IRQ_HANDLED;
}
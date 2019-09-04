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
struct malidp_hw_device {int pm_suspended; int /*<<< orphan*/  pclk; int /*<<< orphan*/  aclk; int /*<<< orphan*/  mclk; TYPE_1__* hw; } ;
struct malidp_drm {struct malidp_hw_device* dev; } ;
struct drm_device {struct malidp_drm* dev_private; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* in_config_mode ) (struct malidp_hw_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  malidp_de_irq_fini (struct malidp_hw_device*) ; 
 int /*<<< orphan*/  malidp_se_irq_fini (struct malidp_hw_device*) ; 
 int /*<<< orphan*/  stub1 (struct malidp_hw_device*) ; 

__attribute__((used)) static int malidp_runtime_pm_suspend(struct device *dev)
{
	struct drm_device *drm = dev_get_drvdata(dev);
	struct malidp_drm *malidp = drm->dev_private;
	struct malidp_hw_device *hwdev = malidp->dev;

	/* we can only suspend if the hardware is in config mode */
	WARN_ON(!hwdev->hw->in_config_mode(hwdev));

	malidp_se_irq_fini(hwdev);
	malidp_de_irq_fini(hwdev);
	hwdev->pm_suspended = true;
	clk_disable_unprepare(hwdev->mclk);
	clk_disable_unprepare(hwdev->aclk);
	clk_disable_unprepare(hwdev->pclk);

	return 0;
}
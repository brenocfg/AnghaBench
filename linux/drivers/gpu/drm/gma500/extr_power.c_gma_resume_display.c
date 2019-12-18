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
struct pci_dev {int dummy; } ;
struct drm_psb_private {int suspended; int display_power; int pge_ctl; int gmch_ctrl; TYPE_1__* ops; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* restore_regs ) (struct drm_device*) ;int /*<<< orphan*/  (* power_up ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PSB_GMCH_CTRL ; 
 int /*<<< orphan*/  PSB_PGETBL_CTL ; 
 int /*<<< orphan*/  PSB_WVDC32 (int,int /*<<< orphan*/ ) ; 
 int _PSB_GMCH_ENABLED ; 
 int _PSB_PGETBL_ENABLED ; 
 struct drm_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psb_gtt_restore (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*) ; 

__attribute__((used)) static void gma_resume_display(struct pci_dev *pdev)
{
	struct drm_device *dev = pci_get_drvdata(pdev);
	struct drm_psb_private *dev_priv = dev->dev_private;

	/* turn on the display power island */
	dev_priv->ops->power_up(dev);
	dev_priv->suspended = false;
	dev_priv->display_power = true;

	PSB_WVDC32(dev_priv->pge_ctl | _PSB_PGETBL_ENABLED, PSB_PGETBL_CTL);
	pci_write_config_word(pdev, PSB_GMCH_CTRL,
			dev_priv->gmch_ctrl | _PSB_GMCH_ENABLED);

	psb_gtt_restore(dev); /* Rebuild our GTT mappings */
	dev_priv->ops->restore_regs(dev);
}
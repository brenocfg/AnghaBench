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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct malidp_hw_device {int dummy; } ;
struct malidp_drm {struct malidp_hw_device* dev; } ;
struct drm_device {struct malidp_drm* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct drm_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malidp_de_irq_fini (struct malidp_hw_device*) ; 
 int malidp_de_irq_init (struct drm_device*,int) ; 
 int malidp_se_irq_init (struct drm_device*,int) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 

__attribute__((used)) static int malidp_irq_init(struct platform_device *pdev)
{
	int irq_de, irq_se, ret = 0;
	struct drm_device *drm = dev_get_drvdata(&pdev->dev);
	struct malidp_drm *malidp = drm->dev_private;
	struct malidp_hw_device *hwdev = malidp->dev;

	/* fetch the interrupts from DT */
	irq_de = platform_get_irq_byname(pdev, "DE");
	if (irq_de < 0) {
		DRM_ERROR("no 'DE' IRQ specified!\n");
		return irq_de;
	}
	irq_se = platform_get_irq_byname(pdev, "SE");
	if (irq_se < 0) {
		DRM_ERROR("no 'SE' IRQ specified!\n");
		return irq_se;
	}

	ret = malidp_de_irq_init(drm, irq_de);
	if (ret)
		return ret;

	ret = malidp_se_irq_init(drm, irq_se);
	if (ret) {
		malidp_de_irq_fini(hwdev);
		return ret;
	}

	return 0;
}
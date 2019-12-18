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
struct malidp_hw_device {int dummy; } ;
struct malidp_drm {struct malidp_hw_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; struct malidp_drm* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  MALIDP_DC_BLOCK ; 
 int /*<<< orphan*/  MALIDP_DE_BLOCK ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct drm_device*) ; 
 int /*<<< orphan*/  malidp_de_irq ; 
 int /*<<< orphan*/  malidp_de_irq_hw_init (struct malidp_hw_device*) ; 
 int /*<<< orphan*/  malidp_de_irq_thread_handler ; 
 int /*<<< orphan*/  malidp_hw_clear_irq (struct malidp_hw_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  malidp_hw_disable_irq (struct malidp_hw_device*,int /*<<< orphan*/ ,int) ; 

int malidp_de_irq_init(struct drm_device *drm, int irq)
{
	struct malidp_drm *malidp = drm->dev_private;
	struct malidp_hw_device *hwdev = malidp->dev;
	int ret;

	/* ensure interrupts are disabled */
	malidp_hw_disable_irq(hwdev, MALIDP_DE_BLOCK, 0xffffffff);
	malidp_hw_clear_irq(hwdev, MALIDP_DE_BLOCK, 0xffffffff);
	malidp_hw_disable_irq(hwdev, MALIDP_DC_BLOCK, 0xffffffff);
	malidp_hw_clear_irq(hwdev, MALIDP_DC_BLOCK, 0xffffffff);

	ret = devm_request_threaded_irq(drm->dev, irq, malidp_de_irq,
					malidp_de_irq_thread_handler,
					IRQF_SHARED, "malidp-de", drm);
	if (ret < 0) {
		DRM_ERROR("failed to install DE IRQ handler\n");
		return ret;
	}

	malidp_de_irq_hw_init(hwdev);

	return 0;
}
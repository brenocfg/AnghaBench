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
struct TYPE_2__ {int /*<<< orphan*/  mmu_features; } ;
struct panfrost_device {int /*<<< orphan*/  dev; TYPE_1__ features; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  FIELD_GET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct panfrost_device*) ; 
 int /*<<< orphan*/  dma_set_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panfrost_gpu_init_features (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_gpu_init_quirks (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_gpu_irq_handler ; 
 int /*<<< orphan*/  panfrost_gpu_power_on (struct panfrost_device*) ; 
 int panfrost_gpu_soft_reset (struct panfrost_device*) ; 
 int platform_get_irq_byname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ ) ; 

int panfrost_gpu_init(struct panfrost_device *pfdev)
{
	int err, irq;

	err = panfrost_gpu_soft_reset(pfdev);
	if (err)
		return err;

	panfrost_gpu_init_features(pfdev);

	dma_set_mask_and_coherent(pfdev->dev,
		DMA_BIT_MASK(FIELD_GET(0xff00, pfdev->features.mmu_features)));

	irq = platform_get_irq_byname(to_platform_device(pfdev->dev), "gpu");
	if (irq <= 0)
		return -ENODEV;

	err = devm_request_irq(pfdev->dev, irq, panfrost_gpu_irq_handler,
			       IRQF_SHARED, "gpu", pfdev);
	if (err) {
		dev_err(pfdev->dev, "failed to request gpu irq");
		return err;
	}

	panfrost_gpu_init_quirks(pfdev);
	panfrost_gpu_power_on(pfdev);

	return 0;
}
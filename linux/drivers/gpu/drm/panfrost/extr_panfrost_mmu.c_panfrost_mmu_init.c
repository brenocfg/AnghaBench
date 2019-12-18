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
struct panfrost_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_mmu_irq_handler ; 
 int /*<<< orphan*/  panfrost_mmu_irq_handler_thread ; 
 int platform_get_irq_byname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ ) ; 

int panfrost_mmu_init(struct panfrost_device *pfdev)
{
	int err, irq;

	irq = platform_get_irq_byname(to_platform_device(pfdev->dev), "mmu");
	if (irq <= 0)
		return -ENODEV;

	err = devm_request_threaded_irq(pfdev->dev, irq, panfrost_mmu_irq_handler,
					panfrost_mmu_irq_handler_thread,
					IRQF_SHARED, "mmu", pfdev);

	if (err) {
		dev_err(pfdev->dev, "failed to request mmu irq");
		return err;
	}

	return 0;
}
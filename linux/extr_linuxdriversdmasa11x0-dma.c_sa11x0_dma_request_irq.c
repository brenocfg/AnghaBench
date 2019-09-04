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

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sa11x0_dma_irq ; 

__attribute__((used)) static int sa11x0_dma_request_irq(struct platform_device *pdev, int nr,
	void *data)
{
	int irq = platform_get_irq(pdev, nr);

	if (irq <= 0)
		return -ENXIO;

	return request_irq(irq, sa11x0_dma_irq, 0, dev_name(&pdev->dev), data);
}
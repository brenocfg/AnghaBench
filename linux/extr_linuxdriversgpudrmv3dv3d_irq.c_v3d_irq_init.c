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
struct v3d_dev {int cores; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; int /*<<< orphan*/  overflow_mem_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  V3D_CORE_IRQS ; 
 int /*<<< orphan*/  V3D_CORE_WRITE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_CTL_INT_CLR ; 
 int /*<<< orphan*/  V3D_HUB_INT_CLR ; 
 int /*<<< orphan*/  V3D_HUB_IRQS ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct v3d_dev*) ; 
 int /*<<< orphan*/  platform_get_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v3d_hub_irq ; 
 int /*<<< orphan*/  v3d_irq ; 
 int /*<<< orphan*/  v3d_irq_enable (struct v3d_dev*) ; 
 int /*<<< orphan*/  v3d_overflow_mem_work ; 

void
v3d_irq_init(struct v3d_dev *v3d)
{
	int ret, core;

	INIT_WORK(&v3d->overflow_mem_work, v3d_overflow_mem_work);

	/* Clear any pending interrupts someone might have left around
	 * for us.
	 */
	for (core = 0; core < v3d->cores; core++)
		V3D_CORE_WRITE(core, V3D_CTL_INT_CLR, V3D_CORE_IRQS);
	V3D_WRITE(V3D_HUB_INT_CLR, V3D_HUB_IRQS);

	ret = devm_request_irq(v3d->dev, platform_get_irq(v3d->pdev, 0),
			       v3d_hub_irq, IRQF_SHARED,
			       "v3d_hub", v3d);
	ret = devm_request_irq(v3d->dev, platform_get_irq(v3d->pdev, 1),
			       v3d_irq, IRQF_SHARED,
			       "v3d_core0", v3d);
	if (ret)
		dev_err(v3d->dev, "IRQ setup failed: %d\n", ret);

	v3d_irq_enable(v3d);
}
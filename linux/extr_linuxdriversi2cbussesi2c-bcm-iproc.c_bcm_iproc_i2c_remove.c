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
struct platform_device {int dummy; } ;
struct bcm_iproc_i2c_dev {int /*<<< orphan*/  adapter; int /*<<< orphan*/  irq; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IE_OFFSET ; 
 int /*<<< orphan*/  bcm_iproc_i2c_enable_disable (struct bcm_iproc_i2c_dev*,int) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct bcm_iproc_i2c_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bcm_iproc_i2c_remove(struct platform_device *pdev)
{
	struct bcm_iproc_i2c_dev *iproc_i2c = platform_get_drvdata(pdev);

	/* make sure there's no pending interrupt when we remove the adapter */
	writel(0, iproc_i2c->base + IE_OFFSET);
	readl(iproc_i2c->base + IE_OFFSET);
	synchronize_irq(iproc_i2c->irq);

	i2c_del_adapter(&iproc_i2c->adapter);
	bcm_iproc_i2c_enable_disable(iproc_i2c, false);

	return 0;
}
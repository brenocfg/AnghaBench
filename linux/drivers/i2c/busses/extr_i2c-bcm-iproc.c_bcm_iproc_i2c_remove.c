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
struct bcm_iproc_i2c_dev {int /*<<< orphan*/  adapter; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_OFFSET ; 
 int /*<<< orphan*/  bcm_iproc_i2c_enable_disable (struct bcm_iproc_i2c_dev*,int) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iproc_i2c_rd_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_i2c_wr_reg (struct bcm_iproc_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm_iproc_i2c_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  synchronize_irq (scalar_t__) ; 

__attribute__((used)) static int bcm_iproc_i2c_remove(struct platform_device *pdev)
{
	struct bcm_iproc_i2c_dev *iproc_i2c = platform_get_drvdata(pdev);

	if (iproc_i2c->irq) {
		/*
		 * Make sure there's no pending interrupt when we remove the
		 * adapter
		 */
		iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, 0);
		iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
		synchronize_irq(iproc_i2c->irq);
	}

	i2c_del_adapter(&iproc_i2c->adapter);
	bcm_iproc_i2c_enable_disable(iproc_i2c, false);

	return 0;
}
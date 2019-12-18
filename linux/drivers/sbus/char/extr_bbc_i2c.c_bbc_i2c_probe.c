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
struct TYPE_2__ {int /*<<< orphan*/ * irqs; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * resource; TYPE_1__ archdata; } ;
struct bbc_i2c_bus {scalar_t__ i2c_control_regs; scalar_t__ i2c_bussel_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 struct bbc_i2c_bus* attach_one_i2c (struct platform_device*,int) ; 
 int bbc_envctrl_init (struct bbc_i2c_bus*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct bbc_i2c_bus*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bbc_i2c_bus*) ; 
 int /*<<< orphan*/  kfree (struct bbc_i2c_bus*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int bbc_i2c_probe(struct platform_device *op)
{
	struct bbc_i2c_bus *bp;
	int err, index = 0;

	bp = attach_one_i2c(op, index);
	if (!bp)
		return -EINVAL;

	err = bbc_envctrl_init(bp);
	if (err) {
		free_irq(op->archdata.irqs[0], bp);
		if (bp->i2c_bussel_reg)
			of_iounmap(&op->resource[0], bp->i2c_bussel_reg, 1);
		if (bp->i2c_control_regs)
			of_iounmap(&op->resource[1], bp->i2c_control_regs, 2);
		kfree(bp);
	} else {
		dev_set_drvdata(&op->dev, bp);
	}

	return err;
}
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
struct mpc_i2c {int /*<<< orphan*/  base; scalar_t__ irq; scalar_t__ clk_per; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct mpc_i2c*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct mpc_i2c*) ; 
 struct mpc_i2c* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int fsl_i2c_remove(struct platform_device *op)
{
	struct mpc_i2c *i2c = platform_get_drvdata(op);

	i2c_del_adapter(&i2c->adap);

	if (i2c->clk_per)
		clk_disable_unprepare(i2c->clk_per);

	if (i2c->irq)
		free_irq(i2c->irq, i2c);

	irq_dispose_mapping(i2c->irq);
	iounmap(i2c->base);
	kfree(i2c);
	return 0;
}
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
struct dpio_priv {int /*<<< orphan*/  io; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 struct dpio_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dpaa2_io_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dpio_irq_handler(int irq_num, void *arg)
{
	struct device *dev = (struct device *)arg;
	struct dpio_priv *priv = dev_get_drvdata(dev);

	return dpaa2_io_irq(priv->io);
}
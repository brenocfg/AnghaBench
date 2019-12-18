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
struct TYPE_2__ {int started; } ;
struct xgbe_prv_data {scalar_t__ dev_irq; scalar_t__ i2c_irq; TYPE_1__ i2c; int /*<<< orphan*/  netdev; int /*<<< orphan*/  i2c_name; int /*<<< orphan*/  dev; int /*<<< orphan*/  tasklet_i2c; } ;

/* Variables and functions */
 int devm_request_irq (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  xgbe_i2c_isr ; 
 int /*<<< orphan*/  xgbe_i2c_isr_task ; 

__attribute__((used)) static int xgbe_i2c_start(struct xgbe_prv_data *pdata)
{
	int ret;

	if (pdata->i2c.started)
		return 0;

	netif_dbg(pdata, link, pdata->netdev, "starting I2C\n");

	/* If we have a separate I2C irq, enable it */
	if (pdata->dev_irq != pdata->i2c_irq) {
		tasklet_init(&pdata->tasklet_i2c, xgbe_i2c_isr_task,
			     (unsigned long)pdata);

		ret = devm_request_irq(pdata->dev, pdata->i2c_irq,
				       xgbe_i2c_isr, 0, pdata->i2c_name,
				       pdata);
		if (ret) {
			netdev_err(pdata->netdev, "i2c irq request failed\n");
			return ret;
		}
	}

	pdata->i2c.started = 1;

	return 0;
}
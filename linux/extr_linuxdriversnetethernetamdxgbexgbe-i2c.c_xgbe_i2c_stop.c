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
struct TYPE_2__ {scalar_t__ started; } ;
struct xgbe_prv_data {scalar_t__ dev_irq; scalar_t__ i2c_irq; int /*<<< orphan*/  dev; TYPE_1__ i2c; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,scalar_t__,struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xgbe_i2c_clear_all_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_disable (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_disable_interrupts (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_i2c_stop(struct xgbe_prv_data *pdata)
{
	if (!pdata->i2c.started)
		return;

	netif_dbg(pdata, link, pdata->netdev, "stopping I2C\n");

	pdata->i2c.started = 0;

	xgbe_i2c_disable_interrupts(pdata);
	xgbe_i2c_disable(pdata);
	xgbe_i2c_clear_all_interrupts(pdata);

	if (pdata->dev_irq != pdata->i2c_irq)
		devm_free_irq(pdata->dev, pdata->i2c_irq, pdata);
}
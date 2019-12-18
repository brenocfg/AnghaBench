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
struct xgbe_prv_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xgbe_i2c_clear_all_interrupts (struct xgbe_prv_data*) ; 
 int xgbe_i2c_disable (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_disable_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_get_features (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_i2c_set_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_i2c_init(struct xgbe_prv_data *pdata)
{
	int ret;

	xgbe_i2c_disable_interrupts(pdata);

	ret = xgbe_i2c_disable(pdata);
	if (ret) {
		dev_err(pdata->dev, "failed to disable i2c master\n");
		return ret;
	}

	xgbe_i2c_get_features(pdata);

	xgbe_i2c_set_mode(pdata);

	xgbe_i2c_clear_all_interrupts(pdata);

	return 0;
}
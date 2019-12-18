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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 unsigned int xgbe_i2c_abort (struct xgbe_prv_data*) ; 
 unsigned int xgbe_i2c_set_enable (struct xgbe_prv_data*,int) ; 

__attribute__((used)) static int xgbe_i2c_disable(struct xgbe_prv_data *pdata)
{
	unsigned int ret;

	ret = xgbe_i2c_set_enable(pdata, false);
	if (ret) {
		/* Disable failed, try an abort */
		ret = xgbe_i2c_abort(pdata);
		if (ret)
			return ret;

		/* Abort succeeded, try to disable again */
		ret = xgbe_i2c_set_enable(pdata, false);
	}

	return ret;
}
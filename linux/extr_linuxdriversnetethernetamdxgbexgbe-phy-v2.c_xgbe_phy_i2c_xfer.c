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
struct TYPE_2__ {int (* i2c_xfer ) (struct xgbe_prv_data*,struct xgbe_i2c_op*) ;} ;
struct xgbe_prv_data {TYPE_1__ i2c_if; } ;
struct xgbe_i2c_op {int dummy; } ;

/* Variables and functions */
 int stub1 (struct xgbe_prv_data*,struct xgbe_i2c_op*) ; 

__attribute__((used)) static int xgbe_phy_i2c_xfer(struct xgbe_prv_data *pdata,
			     struct xgbe_i2c_op *i2c_op)
{
	return pdata->i2c_if.i2c_xfer(pdata, i2c_op);
}
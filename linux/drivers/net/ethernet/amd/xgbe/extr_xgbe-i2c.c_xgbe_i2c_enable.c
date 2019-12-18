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
 int xgbe_i2c_set_enable (struct xgbe_prv_data*,int) ; 

__attribute__((used)) static int xgbe_i2c_enable(struct xgbe_prv_data *pdata)
{
	return xgbe_i2c_set_enable(pdata, true);
}
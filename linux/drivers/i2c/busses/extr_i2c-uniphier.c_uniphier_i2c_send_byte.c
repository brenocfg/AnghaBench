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
typedef  int u32 ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENXIO ; 
 int UNIPHIER_I2C_DREC_LAB ; 
 int UNIPHIER_I2C_DREC_LRB ; 
 int uniphier_i2c_xfer_byte (struct i2c_adapter*,int,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int uniphier_i2c_send_byte(struct i2c_adapter *adap, u32 txdata)
{
	u32 rxdata;
	int ret;

	ret = uniphier_i2c_xfer_byte(adap, txdata, &rxdata);
	if (ret)
		return ret;

	if (unlikely(rxdata & UNIPHIER_I2C_DREC_LAB))
		return -EAGAIN;

	if (unlikely(rxdata & UNIPHIER_I2C_DREC_LRB))
		return -ENXIO;

	return 0;
}
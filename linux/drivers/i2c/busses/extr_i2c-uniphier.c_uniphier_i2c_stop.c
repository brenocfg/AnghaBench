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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int UNIPHIER_I2C_DTRM_NACK ; 
 int UNIPHIER_I2C_DTRM_STO ; 
 int uniphier_i2c_send_byte (struct i2c_adapter*,int) ; 

__attribute__((used)) static int uniphier_i2c_stop(struct i2c_adapter *adap)
{
	return uniphier_i2c_send_byte(adap, UNIPHIER_I2C_DTRM_STO |
				      UNIPHIER_I2C_DTRM_NACK);
}
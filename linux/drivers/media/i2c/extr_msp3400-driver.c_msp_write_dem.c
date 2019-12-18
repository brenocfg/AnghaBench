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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_MSP_DEM ; 
 int msp_write (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 

int msp_write_dem(struct i2c_client *client, int addr, int val)
{
	return msp_write(client, I2C_MSP_DEM, addr, val);
}
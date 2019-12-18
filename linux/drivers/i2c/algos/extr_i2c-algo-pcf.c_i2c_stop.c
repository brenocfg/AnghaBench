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
struct i2c_algo_pcf_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBPROTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_PCF_STOP ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  set_pcf (struct i2c_algo_pcf_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_stop(struct i2c_algo_pcf_data *adap)
{
	DEBPROTO(printk("P\n"));
	set_pcf(adap, 1, I2C_PCF_STOP);
}
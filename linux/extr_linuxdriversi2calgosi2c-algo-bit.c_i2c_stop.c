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
struct i2c_algo_bit_data {int /*<<< orphan*/  udelay; } ;

/* Variables and functions */
 int /*<<< orphan*/  sclhi (struct i2c_algo_bit_data*) ; 
 int /*<<< orphan*/  sdalo (struct i2c_algo_bit_data*) ; 
 int /*<<< orphan*/  setsda (struct i2c_algo_bit_data*,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_stop(struct i2c_algo_bit_data *adap)
{
	/* assert: scl is low */
	sdalo(adap);
	sclhi(adap);
	setsda(adap, 1);
	udelay(adap->udelay);
}
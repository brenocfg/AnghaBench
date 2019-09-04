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
struct i2c_algo_iop3xx_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP3XX_ISR_UNITBUSY ; 
 int /*<<< orphan*/  all_bits_clear ; 
 int iop3xx_i2c_wait_event (struct i2c_algo_iop3xx_data*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iop3xx_i2c_wait_idle(struct i2c_algo_iop3xx_data *iop3xx_adap, int *status)
{
	return iop3xx_i2c_wait_event(
		iop3xx_adap, IOP3XX_ISR_UNITBUSY, status, all_bits_clear);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  complete; int /*<<< orphan*/  ret; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct i2c_pnx_algo_data {TYPE_1__ mif; TYPE_2__ adapter; } ;
struct TYPE_6__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  I2C_REG_CTL (struct i2c_pnx_algo_data*) ; 
 int /*<<< orphan*/  I2C_REG_STS (struct i2c_pnx_algo_data*) ; 
 struct i2c_pnx_algo_data* alg_data ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 struct i2c_pnx_algo_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int mcntrl_afie ; 
 int mcntrl_drmie ; 
 int mcntrl_naie ; 
 int mcntrl_reset ; 
 int mcntrl_rffie ; 
 TYPE_3__ mif ; 
 int /*<<< orphan*/  wait_reset (struct i2c_pnx_algo_data*) ; 

__attribute__((used)) static void i2c_pnx_timeout(struct timer_list *t)
{
	struct i2c_pnx_algo_data *alg_data = from_timer(alg_data, t, mif.timer);
	u32 ctl;

	dev_err(&alg_data->adapter.dev,
		"Master timed out. stat = %04x, cntrl = %04x. Resetting master...\n",
		ioread32(I2C_REG_STS(alg_data)),
		ioread32(I2C_REG_CTL(alg_data)));

	/* Reset master and disable interrupts */
	ctl = ioread32(I2C_REG_CTL(alg_data));
	ctl &= ~(mcntrl_afie | mcntrl_naie | mcntrl_rffie | mcntrl_drmie);
	iowrite32(ctl, I2C_REG_CTL(alg_data));

	ctl |= mcntrl_reset;
	iowrite32(ctl, I2C_REG_CTL(alg_data));
	wait_reset(alg_data);
	alg_data->mif.ret = -EIO;
	complete(&alg_data->mif.complete);
}
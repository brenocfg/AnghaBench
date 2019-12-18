#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mt9t112_priv {TYPE_2__* info; } ;
struct i2c_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  p7; int /*<<< orphan*/  p6; int /*<<< orphan*/  p5; int /*<<< orphan*/  p4; int /*<<< orphan*/  p3; int /*<<< orphan*/  p2; int /*<<< orphan*/  p1; int /*<<< orphan*/  n; int /*<<< orphan*/  m; } ;
struct TYPE_4__ {TYPE_1__ divider; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mt9t112_reg_mask_set (int,struct i2c_client const*,int,int,int) ; 
 int /*<<< orphan*/  mt9t112_reg_read (int,struct i2c_client const*,int) ; 
 int /*<<< orphan*/  mt9t112_reg_write (int,struct i2c_client const*,int,int) ; 
 int /*<<< orphan*/  mt9t112_set_pll_dividers (struct i2c_client const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt9t112_priv* to_mt9t112 (struct i2c_client const*) ; 

__attribute__((used)) static int mt9t112_init_pll(const struct i2c_client *client)
{
	struct mt9t112_priv *priv = to_mt9t112(client);
	int data, i, ret;

	mt9t112_reg_mask_set(ret, client, 0x0014, 0x003, 0x0001);

	/* PLL control: BYPASS PLL = 8517. */
	mt9t112_reg_write(ret, client, 0x0014, 0x2145);

	/* Replace these registers when new timing parameters are generated. */
	mt9t112_set_pll_dividers(client,
				 priv->info->divider.m, priv->info->divider.n,
				 priv->info->divider.p1, priv->info->divider.p2,
				 priv->info->divider.p3, priv->info->divider.p4,
				 priv->info->divider.p5, priv->info->divider.p6,
				 priv->info->divider.p7);

	/*
	 * TEST_BYPASS  on
	 * PLL_ENABLE   on
	 * SEL_LOCK_DET on
	 * TEST_BYPASS  off
	 */
	mt9t112_reg_write(ret, client, 0x0014, 0x2525);
	mt9t112_reg_write(ret, client, 0x0014, 0x2527);
	mt9t112_reg_write(ret, client, 0x0014, 0x3427);
	mt9t112_reg_write(ret, client, 0x0014, 0x3027);

	mdelay(10);

	/*
	 * PLL_BYPASS off
	 * Reference clock count
	 * I2C Master Clock Divider
	 */
	mt9t112_reg_write(ret, client, 0x0014, 0x3046);
	/* JPEG initialization workaround */
	mt9t112_reg_write(ret, client, 0x0016, 0x0400);
	mt9t112_reg_write(ret, client, 0x0022, 0x0190);
	mt9t112_reg_write(ret, client, 0x3B84, 0x0212);

	/* External sensor clock is PLL bypass. */
	mt9t112_reg_write(ret, client, 0x002E, 0x0500);

	mt9t112_reg_mask_set(ret, client, 0x0018, 0x0002, 0x0002);
	mt9t112_reg_mask_set(ret, client, 0x3B82, 0x0004, 0x0004);

	/* MCU disabled. */
	mt9t112_reg_mask_set(ret, client, 0x0018, 0x0004, 0x0004);

	/* Out of standby. */
	mt9t112_reg_mask_set(ret, client, 0x0018, 0x0001, 0);

	mdelay(50);

	/*
	 * Standby Workaround
	 * Disable Secondary I2C Pads
	 */
	mt9t112_reg_write(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_write(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_write(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_write(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_write(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_write(ret, client, 0x0614, 0x0001);
	mdelay(1);

	/* Poll to verify out of standby. Must Poll this bit. */
	for (i = 0; i < 100; i++) {
		mt9t112_reg_read(data, client, 0x0018);
		if (!(data & 0x4000))
			break;

		mdelay(10);
	}

	return ret;
}
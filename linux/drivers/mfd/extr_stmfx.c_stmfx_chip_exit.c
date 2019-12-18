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
struct stmfx {scalar_t__ vdd; int /*<<< orphan*/  map; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMFX_REG_IRQ_SRC_EN ; 
 int /*<<< orphan*/  STMFX_REG_SYS_CTRL ; 
 struct stmfx* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_disable (scalar_t__) ; 

__attribute__((used)) static int stmfx_chip_exit(struct i2c_client *client)
{
	struct stmfx *stmfx = i2c_get_clientdata(client);

	regmap_write(stmfx->map, STMFX_REG_IRQ_SRC_EN, 0);
	regmap_write(stmfx->map, STMFX_REG_SYS_CTRL, 0);

	if (stmfx->vdd)
		return regulator_disable(stmfx->vdd);

	return 0;
}
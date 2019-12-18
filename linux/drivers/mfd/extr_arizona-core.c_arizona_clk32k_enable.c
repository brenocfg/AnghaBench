#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int clk32k_src; } ;
struct arizona {int clk32k_ref; int /*<<< orphan*/  clk_lock; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * mclk; int /*<<< orphan*/  dev; TYPE_1__ pdata; } ;

/* Variables and functions */
#define  ARIZONA_32KZ_MCLK1 129 
#define  ARIZONA_32KZ_MCLK2 128 
 int /*<<< orphan*/  ARIZONA_CLK_32K_ENA ; 
 int /*<<< orphan*/  ARIZONA_CLOCK_32K_1 ; 
 size_t ARIZONA_MCLK1 ; 
 size_t ARIZONA_MCLK2 ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int arizona_clk32k_enable(struct arizona *arizona)
{
	int ret = 0;

	mutex_lock(&arizona->clk_lock);

	arizona->clk32k_ref++;

	if (arizona->clk32k_ref == 1) {
		switch (arizona->pdata.clk32k_src) {
		case ARIZONA_32KZ_MCLK1:
			ret = pm_runtime_get_sync(arizona->dev);
			if (ret != 0)
				goto err_ref;
			ret = clk_prepare_enable(arizona->mclk[ARIZONA_MCLK1]);
			if (ret != 0) {
				pm_runtime_put_sync(arizona->dev);
				goto err_ref;
			}
			break;
		case ARIZONA_32KZ_MCLK2:
			ret = clk_prepare_enable(arizona->mclk[ARIZONA_MCLK2]);
			if (ret != 0)
				goto err_ref;
			break;
		}

		ret = regmap_update_bits(arizona->regmap, ARIZONA_CLOCK_32K_1,
					 ARIZONA_CLK_32K_ENA,
					 ARIZONA_CLK_32K_ENA);
	}

err_ref:
	if (ret != 0)
		arizona->clk32k_ref--;

	mutex_unlock(&arizona->clk_lock);

	return ret;
}
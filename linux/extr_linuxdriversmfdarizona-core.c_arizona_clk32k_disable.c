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
struct arizona {scalar_t__ clk32k_ref; int /*<<< orphan*/  clk_lock; int /*<<< orphan*/ * mclk; int /*<<< orphan*/  dev; TYPE_1__ pdata; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  ARIZONA_32KZ_MCLK1 129 
#define  ARIZONA_32KZ_MCLK2 128 
 int /*<<< orphan*/  ARIZONA_CLK_32K_ENA ; 
 int /*<<< orphan*/  ARIZONA_CLOCK_32K_1 ; 
 size_t ARIZONA_MCLK1 ; 
 size_t ARIZONA_MCLK2 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int arizona_clk32k_disable(struct arizona *arizona)
{
	mutex_lock(&arizona->clk_lock);

	BUG_ON(arizona->clk32k_ref <= 0);

	arizona->clk32k_ref--;

	if (arizona->clk32k_ref == 0) {
		regmap_update_bits(arizona->regmap, ARIZONA_CLOCK_32K_1,
				   ARIZONA_CLK_32K_ENA, 0);

		switch (arizona->pdata.clk32k_src) {
		case ARIZONA_32KZ_MCLK1:
			pm_runtime_put_sync(arizona->dev);
			clk_disable_unprepare(arizona->mclk[ARIZONA_MCLK1]);
			break;
		case ARIZONA_32KZ_MCLK2:
			clk_disable_unprepare(arizona->mclk[ARIZONA_MCLK2]);
			break;
		}
	}

	mutex_unlock(&arizona->clk_lock);

	return 0;
}
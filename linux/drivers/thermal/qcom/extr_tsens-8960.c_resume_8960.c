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
struct TYPE_2__ {int /*<<< orphan*/  control; int /*<<< orphan*/  threshold; } ;
struct tsens_priv {int num_sensors; TYPE_1__ ctx; struct regmap* tm_map; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTL_ADDR ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  CONFIG_ADDR ; 
 int /*<<< orphan*/  CONFIG_MASK ; 
 int /*<<< orphan*/  SW_RST ; 
 int /*<<< orphan*/  THRESHOLD_ADDR ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resume_8960(struct tsens_priv *priv)
{
	int ret;
	struct regmap *map = priv->tm_map;

	ret = regmap_update_bits(map, CNTL_ADDR, SW_RST, SW_RST);
	if (ret)
		return ret;

	/*
	 * Separate CONFIG restore is not needed only for 8660 as
	 * config is part of CTRL Addr and its restored as such
	 */
	if (priv->num_sensors > 1) {
		ret = regmap_update_bits(map, CONFIG_ADDR, CONFIG_MASK, CONFIG);
		if (ret)
			return ret;
	}

	ret = regmap_write(map, THRESHOLD_ADDR, priv->ctx.threshold);
	if (ret)
		return ret;

	ret = regmap_write(map, CNTL_ADDR, priv->ctx.control);
	if (ret)
		return ret;

	return 0;
}
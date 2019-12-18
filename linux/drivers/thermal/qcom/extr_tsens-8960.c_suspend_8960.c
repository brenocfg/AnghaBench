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
 unsigned int EN ; 
 unsigned int SLP_CLK_ENA ; 
 unsigned int SLP_CLK_ENA_8660 ; 
 int /*<<< orphan*/  THRESHOLD_ADDR ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int suspend_8960(struct tsens_priv *priv)
{
	int ret;
	unsigned int mask;
	struct regmap *map = priv->tm_map;

	ret = regmap_read(map, THRESHOLD_ADDR, &priv->ctx.threshold);
	if (ret)
		return ret;

	ret = regmap_read(map, CNTL_ADDR, &priv->ctx.control);
	if (ret)
		return ret;

	if (priv->num_sensors > 1)
		mask = SLP_CLK_ENA | EN;
	else
		mask = SLP_CLK_ENA_8660 | EN;

	ret = regmap_update_bits(map, CNTL_ADDR, mask, 0);
	if (ret)
		return ret;

	return 0;
}
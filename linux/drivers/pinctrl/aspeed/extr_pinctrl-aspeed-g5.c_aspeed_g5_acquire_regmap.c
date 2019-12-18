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
struct regmap {int dummy; } ;
struct device_node {struct device_node* parent; } ;
struct aspeed_pinmux_data {TYPE_1__* dev; struct regmap** maps; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ASPEED_IP_GFX ; 
 int ASPEED_IP_LPC ; 
 int ASPEED_IP_SCU ; 
 int ASPEED_NR_PINMUX_IPS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct regmap* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 scalar_t__ likely (struct regmap*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static struct regmap *aspeed_g5_acquire_regmap(struct aspeed_pinmux_data *ctx,
					       int ip)
{
	if (ip == ASPEED_IP_SCU) {
		WARN(!ctx->maps[ip], "Missing SCU syscon!");
		return ctx->maps[ip];
	}

	if (ip >= ASPEED_NR_PINMUX_IPS)
		return ERR_PTR(-EINVAL);

	if (likely(ctx->maps[ip]))
		return ctx->maps[ip];

	if (ip == ASPEED_IP_GFX) {
		struct device_node *node;
		struct regmap *map;

		node = of_parse_phandle(ctx->dev->of_node,
					"aspeed,external-nodes", 0);
		if (node) {
			map = syscon_node_to_regmap(node);
			of_node_put(node);
			if (IS_ERR(map))
				return map;
		} else
			return ERR_PTR(-ENODEV);

		ctx->maps[ASPEED_IP_GFX] = map;
		dev_dbg(ctx->dev, "Acquired GFX regmap");
		return map;
	}

	if (ip == ASPEED_IP_LPC) {
		struct device_node *node;
		struct regmap *map;

		node = of_parse_phandle(ctx->dev->of_node,
					"aspeed,external-nodes", 1);
		if (node) {
			map = syscon_node_to_regmap(node->parent);
			of_node_put(node);
			if (IS_ERR(map))
				return map;
		} else
			return ERR_PTR(-ENODEV);

		ctx->maps[ASPEED_IP_LPC] = map;
		dev_dbg(ctx->dev, "Acquired LPC regmap");
		return map;
	}

	return ERR_PTR(-EINVAL);
}
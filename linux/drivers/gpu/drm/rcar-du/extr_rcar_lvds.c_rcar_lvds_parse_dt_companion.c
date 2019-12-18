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
struct rcar_lvds {int /*<<< orphan*/  companion; struct device* dev; } ;
struct of_device_id {int /*<<< orphan*/  compatible; } ;
struct device_node {int dummy; } ;
struct device {TYPE_1__* driver; int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct device_node*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_drm_find_bridge (struct device_node*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_lvds_parse_dt_companion(struct rcar_lvds *lvds)
{
	const struct of_device_id *match;
	struct device_node *companion;
	struct device *dev = lvds->dev;
	int ret = 0;

	/* Locate the companion LVDS encoder for dual-link operation, if any. */
	companion = of_parse_phandle(dev->of_node, "renesas,companion", 0);
	if (!companion)
		return 0;

	/*
	 * Sanity check: the companion encoder must have the same compatible
	 * string.
	 */
	match = of_match_device(dev->driver->of_match_table, dev);
	if (!of_device_is_compatible(companion, match->compatible)) {
		dev_err(dev, "Companion LVDS encoder is invalid\n");
		ret = -ENXIO;
		goto done;
	}

	lvds->companion = of_drm_find_bridge(companion);
	if (!lvds->companion) {
		ret = -EPROBE_DEFER;
		goto done;
	}

	dev_dbg(dev, "Found companion encoder %pOF\n", companion);

done:
	of_node_put(companion);

	return ret;
}
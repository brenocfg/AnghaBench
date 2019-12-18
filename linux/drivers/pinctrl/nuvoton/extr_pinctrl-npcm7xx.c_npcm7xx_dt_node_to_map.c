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
typedef  int /*<<< orphan*/  u32 ;
struct pinctrl_map {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct npcm7xx_pinctrl {int /*<<< orphan*/  dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_MAP_TYPE_INVALID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int pinconf_generic_dt_node_to_map (struct pinctrl_dev*,struct device_node*,struct pinctrl_map**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct npcm7xx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int npcm7xx_dt_node_to_map(struct pinctrl_dev *pctldev,
				  struct device_node *np_config,
				  struct pinctrl_map **map,
				  u32 *num_maps)
{
	struct npcm7xx_pinctrl *npcm = pinctrl_dev_get_drvdata(pctldev);

	dev_dbg(npcm->dev, "dt_node_to_map: %s\n", np_config->name);
	return pinconf_generic_dt_node_to_map(pctldev, np_config,
					      map, num_maps,
					      PIN_MAP_TYPE_INVALID);
}
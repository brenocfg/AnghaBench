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
struct pinctrl_map {char const* name; void* ctrl_dev_name; void* dev_name; } ;
struct pinctrl_dt_map {unsigned int num_maps; int /*<<< orphan*/  node; struct pinctrl_map* map; struct pinctrl_dev* pctldev; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct pinctrl {int /*<<< orphan*/  dt_maps; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_free_map (struct pinctrl_dev*,struct pinctrl_map*,unsigned int) ; 
 struct pinctrl_dt_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pinctrl_register_map (struct pinctrl_map*,unsigned int,int) ; 

__attribute__((used)) static int dt_remember_or_free_map(struct pinctrl *p, const char *statename,
				   struct pinctrl_dev *pctldev,
				   struct pinctrl_map *map, unsigned num_maps)
{
	int i;
	struct pinctrl_dt_map *dt_map;

	/* Initialize common mapping table entry fields */
	for (i = 0; i < num_maps; i++) {
		map[i].dev_name = dev_name(p->dev);
		map[i].name = statename;
		if (pctldev)
			map[i].ctrl_dev_name = dev_name(pctldev->dev);
	}

	/* Remember the converted mapping table entries */
	dt_map = kzalloc(sizeof(*dt_map), GFP_KERNEL);
	if (!dt_map) {
		dt_free_map(pctldev, map, num_maps);
		return -ENOMEM;
	}

	dt_map->pctldev = pctldev;
	dt_map->map = map;
	dt_map->num_maps = num_maps;
	list_add_tail(&dt_map->node, &p->dt_maps);

	return pinctrl_register_map(map, num_maps, false);
}
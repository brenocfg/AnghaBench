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
struct tegra_hsp_db_map {int /*<<< orphan*/  index; int /*<<< orphan*/  master; scalar_t__ name; } ;
struct tegra_hsp_channel {int dummy; } ;
struct tegra_hsp {TYPE_1__* soc; } ;
struct TYPE_2__ {struct tegra_hsp_db_map* map; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tegra_hsp_channel*) ; 
 int PTR_ERR (struct tegra_hsp_channel*) ; 
 struct tegra_hsp_channel* tegra_hsp_doorbell_create (struct tegra_hsp*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_hsp_add_doorbells(struct tegra_hsp *hsp)
{
	const struct tegra_hsp_db_map *map = hsp->soc->map;
	struct tegra_hsp_channel *channel;

	while (map->name) {
		channel = tegra_hsp_doorbell_create(hsp, map->name,
						    map->master, map->index);
		if (IS_ERR(channel))
			return PTR_ERR(channel);

		map++;
	}

	return 0;
}
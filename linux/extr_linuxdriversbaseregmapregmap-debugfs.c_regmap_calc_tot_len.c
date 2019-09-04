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
struct TYPE_2__ {int val_bytes; } ;
struct regmap {int debugfs_val_len; scalar_t__ debugfs_reg_len; scalar_t__ debugfs_tot_len; TYPE_1__ format; int /*<<< orphan*/  max_register; } ;

/* Variables and functions */
 scalar_t__ regmap_calc_reg_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void regmap_calc_tot_len(struct regmap *map,
				       void *buf, size_t count)
{
	/* Calculate the length of a fixed format  */
	if (!map->debugfs_tot_len) {
		map->debugfs_reg_len = regmap_calc_reg_len(map->max_register),
		map->debugfs_val_len = 2 * map->format.val_bytes;
		map->debugfs_tot_len = map->debugfs_reg_len +
			map->debugfs_val_len + 3;      /* : \n */
	}
}
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
struct map_info {scalar_t__ map_priv_1; } ;
struct latch_addr_flash_info {unsigned long win_mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  data; int /*<<< orphan*/  (* set_window ) (unsigned long,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  map_word ;

/* Variables and functions */
 int /*<<< orphan*/  inline_map_read (struct map_info*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static map_word lf_read(struct map_info *map, unsigned long ofs)
{
	struct latch_addr_flash_info *info;
	map_word datum;

	info = (struct latch_addr_flash_info *)map->map_priv_1;

	spin_lock(&info->lock);

	info->set_window(ofs, info->data);
	datum = inline_map_read(map, info->win_mask & ofs);

	spin_unlock(&info->lock);

	return datum;
}
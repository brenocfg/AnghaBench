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
struct flakey_c {scalar_t__ start; } ;
struct dm_target {struct flakey_c* private; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ dm_target_offset (struct dm_target*,scalar_t__) ; 

__attribute__((used)) static sector_t flakey_map_sector(struct dm_target *ti, sector_t bi_sector)
{
	struct flakey_c *fc = ti->private;

	return fc->start + dm_target_offset(ti, bi_sector);
}
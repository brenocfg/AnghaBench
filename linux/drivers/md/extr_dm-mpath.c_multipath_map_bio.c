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
struct multipath {int dummy; } ;
struct dm_target {struct multipath* private; } ;
struct dm_mpath_io {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int __multipath_map_bio (struct multipath*,struct bio*,struct dm_mpath_io*) ; 
 int /*<<< orphan*/  multipath_init_per_bio_data (struct bio*,struct dm_mpath_io**) ; 

__attribute__((used)) static int multipath_map_bio(struct dm_target *ti, struct bio *bio)
{
	struct multipath *m = ti->private;
	struct dm_mpath_io *mpio = NULL;

	multipath_init_per_bio_data(bio, &mpio);
	return __multipath_map_bio(m, bio, mpio);
}
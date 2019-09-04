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
struct dm_mpath_io {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct dm_mpath_io* dm_per_bio_data (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multipath_per_bio_data_size () ; 

__attribute__((used)) static struct dm_mpath_io *get_mpio_from_bio(struct bio *bio)
{
	return dm_per_bio_data(bio, multipath_per_bio_data_size());
}
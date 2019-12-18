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
typedef  void dm_bio_details ;

/* Variables and functions */

__attribute__((used)) static struct dm_bio_details *get_bio_details_from_mpio(struct dm_mpath_io *mpio)
{
	/* dm_bio_details is immediately after the dm_mpath_io in bio's per-bio-data */
	void *bio_details = mpio + 1;
	return bio_details;
}
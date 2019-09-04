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
struct raid_set {int /*<<< orphan*/  md; int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  RT_FLAG_RS_BITMAP_LOADED ; 
 int md_bitmap_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rs_is_raid0 (struct raid_set*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __load_dirty_region_bitmap(struct raid_set *rs)
{
	int r = 0;

	/* Try loading the bitmap unless "raid0", which does not have one */
	if (!rs_is_raid0(rs) &&
	    !test_and_set_bit(RT_FLAG_RS_BITMAP_LOADED, &rs->runtime_flags)) {
		r = md_bitmap_load(&rs->md);
		if (r)
			DMERR("Failed to load bitmap");
	}

	return r;
}
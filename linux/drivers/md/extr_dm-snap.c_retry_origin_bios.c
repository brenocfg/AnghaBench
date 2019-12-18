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
struct dm_snapshot {int /*<<< orphan*/  origin; } ;
struct bio {struct bio* bi_next; } ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int do_origin (int /*<<< orphan*/ ,struct bio*,int) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 

__attribute__((used)) static void retry_origin_bios(struct dm_snapshot *s, struct bio *bio)
{
	struct bio *n;
	int r;

	while (bio) {
		n = bio->bi_next;
		bio->bi_next = NULL;
		r = do_origin(s->origin, bio, false);
		if (r == DM_MAPIO_REMAPPED)
			generic_make_request(bio);
		bio = n;
	}
}
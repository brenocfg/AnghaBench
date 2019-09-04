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
struct thin_c {int dummy; } ;
struct dm_thin_endio_hook {int /*<<< orphan*/ * cell; int /*<<< orphan*/ * overwrite_mapping; int /*<<< orphan*/ * all_io_entry; int /*<<< orphan*/ * shared_read_entry; struct thin_c* tc; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct dm_thin_endio_hook* dm_per_bio_data (struct bio*,int) ; 

__attribute__((used)) static void thin_hook_bio(struct thin_c *tc, struct bio *bio)
{
	struct dm_thin_endio_hook *h = dm_per_bio_data(bio, sizeof(struct dm_thin_endio_hook));

	h->tc = tc;
	h->shared_read_entry = NULL;
	h->all_io_entry = NULL;
	h->overwrite_mapping = NULL;
	h->cell = NULL;
}
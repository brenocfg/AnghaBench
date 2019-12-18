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
struct dm_thin_new_mapping {int /*<<< orphan*/  status; int /*<<< orphan*/  saved_bi_end_io; } ;
struct dm_thin_endio_hook {struct dm_thin_new_mapping* overwrite_mapping; } ;
struct bio {int /*<<< orphan*/  bi_status; int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_mapping_preparation (struct dm_thin_new_mapping*) ; 
 struct dm_thin_endio_hook* dm_per_bio_data (struct bio*,int) ; 

__attribute__((used)) static void overwrite_endio(struct bio *bio)
{
	struct dm_thin_endio_hook *h = dm_per_bio_data(bio, sizeof(struct dm_thin_endio_hook));
	struct dm_thin_new_mapping *m = h->overwrite_mapping;

	bio->bi_end_io = m->saved_bi_end_io;

	m->status = bio->bi_status;
	complete_mapping_preparation(m);
}
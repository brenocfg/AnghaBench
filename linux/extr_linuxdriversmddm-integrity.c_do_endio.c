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
struct dm_integrity_c {int dummy; } ;
struct bio {scalar_t__ bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int dm_integrity_failed (struct dm_integrity_c*) ; 
 scalar_t__ errno_to_blk_status (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void do_endio(struct dm_integrity_c *ic, struct bio *bio)
{
	int r = dm_integrity_failed(ic);
	if (unlikely(r) && !bio->bi_status)
		bio->bi_status = errno_to_blk_status(r);
	bio_endio(bio);
}
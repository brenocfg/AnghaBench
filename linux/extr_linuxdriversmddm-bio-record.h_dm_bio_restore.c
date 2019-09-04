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
struct dm_bio_details {int /*<<< orphan*/  bi_iter; int /*<<< orphan*/  bi_flags; int /*<<< orphan*/  bi_partno; int /*<<< orphan*/  bi_disk; } ;
struct bio {int /*<<< orphan*/  bi_iter; int /*<<< orphan*/  bi_flags; int /*<<< orphan*/  bi_partno; int /*<<< orphan*/  bi_disk; } ;

/* Variables and functions */

__attribute__((used)) static inline void dm_bio_restore(struct dm_bio_details *bd, struct bio *bio)
{
	bio->bi_disk = bd->bi_disk;
	bio->bi_partno = bd->bi_partno;
	bio->bi_flags = bd->bi_flags;
	bio->bi_iter = bd->bi_iter;
}
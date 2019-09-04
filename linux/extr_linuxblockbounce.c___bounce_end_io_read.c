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
struct bio {int /*<<< orphan*/  bi_status; struct bio* bi_private; } ;
typedef  int /*<<< orphan*/  mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  bounce_end_io (struct bio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_to_high_bio_irq (struct bio*,struct bio*) ; 

__attribute__((used)) static void __bounce_end_io_read(struct bio *bio, mempool_t *pool)
{
	struct bio *bio_orig = bio->bi_private;

	if (!bio->bi_status)
		copy_to_high_bio_irq(bio_orig, bio);

	bounce_end_io(bio, pool);
}
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
struct bio {int /*<<< orphan*/  bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_advance_iter (struct bio*,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ bio_integrity (struct bio*) ; 
 int /*<<< orphan*/  bio_integrity_advance (struct bio*,unsigned int) ; 

void bio_advance(struct bio *bio, unsigned bytes)
{
	if (bio_integrity(bio))
		bio_integrity_advance(bio, bytes);

	bio_advance_iter(bio, &bio->bi_iter, bytes);
}
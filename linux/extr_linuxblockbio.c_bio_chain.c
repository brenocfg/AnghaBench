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
struct bio {scalar_t__ bi_end_io; struct bio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ bio_chain_endio ; 
 int /*<<< orphan*/  bio_inc_remaining (struct bio*) ; 

void bio_chain(struct bio *bio, struct bio *parent)
{
	BUG_ON(bio->bi_private || bio->bi_end_io);

	bio->bi_private = parent;
	bio->bi_end_io	= bio_chain_endio;
	bio_inc_remaining(parent);
}
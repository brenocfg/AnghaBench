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
struct bio {int /*<<< orphan*/  bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  queue_passdown_pt2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void passdown_endio(struct bio *bio)
{
	/*
	 * It doesn't matter if the passdown discard failed, we still want
	 * to unmap (we ignore err).
	 */
	queue_passdown_pt2(bio->bi_private);
	bio_put(bio);
}
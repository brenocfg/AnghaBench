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
struct thin_c {int /*<<< orphan*/  td; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;

/* Variables and functions */
 scalar_t__ dm_thin_changed_this_transaction (int /*<<< orphan*/ ) ; 
 scalar_t__ op_is_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bio_triggers_commit(struct thin_c *tc, struct bio *bio)
{
	return op_is_flush(bio->bi_opf) &&
		dm_thin_changed_this_transaction(tc->td);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache {TYPE_1__* set; } ;
struct bio {int /*<<< orphan*/  bi_status; struct cache* bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_count_io_errors (struct cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  closure_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_super_endio(struct bio *bio)
{
	struct cache *ca = bio->bi_private;

	/* is_read = 0 */
	bch_count_io_errors(ca, bio->bi_status, 0,
			    "writing superblock");
	closure_put(&ca->set->sb_write);
}
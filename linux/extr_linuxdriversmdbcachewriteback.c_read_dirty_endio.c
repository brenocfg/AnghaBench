#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct keybuf_key {int /*<<< orphan*/  key; struct dirty_io* private; } ;
struct dirty_io {TYPE_2__* dc; } ;
struct bio {int /*<<< orphan*/  bi_status; struct keybuf_key* bi_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  c; } ;
struct TYPE_4__ {TYPE_1__ disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTR_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_count_io_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  dirty_endio (struct bio*) ; 

__attribute__((used)) static void read_dirty_endio(struct bio *bio)
{
	struct keybuf_key *w = bio->bi_private;
	struct dirty_io *io = w->private;

	/* is_read = 1 */
	bch_count_io_errors(PTR_CACHE(io->dc->disk.c, &w->key, 0),
			    bio->bi_status, 1,
			    "reading dirty data from cache");

	dirty_endio(bio);
}
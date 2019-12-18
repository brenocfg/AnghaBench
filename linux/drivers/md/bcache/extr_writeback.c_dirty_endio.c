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
struct keybuf_key {int /*<<< orphan*/  key; struct dirty_io* private; } ;
struct dirty_io {int /*<<< orphan*/  cl; int /*<<< orphan*/  dc; } ;
struct bio {scalar_t__ bi_status; struct keybuf_key* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_KEY_DIRTY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bch_count_backing_io_errors (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  closure_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dirty_endio(struct bio *bio)
{
	struct keybuf_key *w = bio->bi_private;
	struct dirty_io *io = w->private;

	if (bio->bi_status) {
		SET_KEY_DIRTY(&w->key, false);
		bch_count_backing_io_errors(io->dc, bio);
	}

	closure_put(&io->cl);
}
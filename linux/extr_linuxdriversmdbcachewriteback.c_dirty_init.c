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
struct TYPE_4__ {int bi_size; } ;
struct bio {struct keybuf_key* bi_private; TYPE_2__ bi_iter; int /*<<< orphan*/  bi_inline_vecs; } ;
struct dirty_io {TYPE_1__* dc; struct bio bio; } ;
struct TYPE_3__ {int /*<<< orphan*/  writeback_percent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOPRIO_CLASS_IDLE ; 
 int /*<<< orphan*/  IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KEY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SECTORS ; 
 int /*<<< orphan*/  bch_bio_map (struct bio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_init (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_prio (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dirty_init(struct keybuf_key *w)
{
	struct dirty_io *io = w->private;
	struct bio *bio = &io->bio;

	bio_init(bio, bio->bi_inline_vecs,
		 DIV_ROUND_UP(KEY_SIZE(&w->key), PAGE_SECTORS));
	if (!io->dc->writeback_percent)
		bio_set_prio(bio, IOPRIO_PRIO_VALUE(IOPRIO_CLASS_IDLE, 0));

	bio->bi_iter.bi_size	= KEY_SIZE(&w->key) << 9;
	bio->bi_private		= w;
	bch_bio_map(bio, NULL);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bi_size; } ;
struct bio {int /*<<< orphan*/ * bi_private; TYPE_1__ bi_iter; int /*<<< orphan*/  bi_inline_vecs; } ;
struct TYPE_5__ {struct bio bio; } ;
struct moving_io {int /*<<< orphan*/  cl; TYPE_3__* w; TYPE_2__ bio; } ;
struct TYPE_6__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOPRIO_CLASS_IDLE ; 
 int /*<<< orphan*/  IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KEY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SECTORS ; 
 int /*<<< orphan*/  bch_bio_map (struct bio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 int /*<<< orphan*/  bio_init (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_prio (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void moving_init(struct moving_io *io)
{
	struct bio *bio = &io->bio.bio;

	bio_init(bio, bio->bi_inline_vecs,
		 DIV_ROUND_UP(KEY_SIZE(&io->w->key), PAGE_SECTORS));
	bio_get(bio);
	bio_set_prio(bio, IOPRIO_PRIO_VALUE(IOPRIO_CLASS_IDLE, 0));

	bio->bi_iter.bi_size	= KEY_SIZE(&io->w->key) << 9;
	bio->bi_private		= &io->cl;
	bch_bio_map(bio, NULL);
}
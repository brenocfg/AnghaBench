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
struct uuid_entry {int /*<<< orphan*/  invalidated; int /*<<< orphan*/  last_reg; int /*<<< orphan*/  first_reg; int /*<<< orphan*/  label; int /*<<< orphan*/  uuid; } ;
struct closure {int dummy; } ;
struct cache_set {int nr_uuids; struct uuid_entry* uuids; int /*<<< orphan*/  uuid_write_mutex; struct closure uuid_write; } ;
struct bkey {int dummy; } ;
struct TYPE_2__ {int bi_size; } ;
struct bio {unsigned long bi_opf; struct closure* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int KEY_PTRS (struct bkey*) ; 
 int KEY_SIZE (struct bkey*) ; 
 unsigned long REQ_META ; 
 int REQ_OP_WRITE ; 
 unsigned long REQ_SYNC ; 
 struct bio* bch_bbio_alloc (struct cache_set*) ; 
 int /*<<< orphan*/  bch_bio_map (struct bio*,struct uuid_entry*) ; 
 int /*<<< orphan*/  bch_extent_to_text (char*,int,struct bkey*) ; 
 int /*<<< orphan*/  bch_is_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bch_submit_bbio (struct bio*,struct cache_set*,struct bkey*,unsigned int) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,unsigned long) ; 
 int /*<<< orphan*/  closure_init (struct closure*,struct closure*) ; 
 int /*<<< orphan*/  closure_return_with_destructor (struct closure*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  uuid_endio ; 
 int /*<<< orphan*/  uuid_io_unlock ; 

__attribute__((used)) static void uuid_io(struct cache_set *c, int op, unsigned long op_flags,
		    struct bkey *k, struct closure *parent)
{
	struct closure *cl = &c->uuid_write;
	struct uuid_entry *u;
	unsigned int i;
	char buf[80];

	BUG_ON(!parent);
	down(&c->uuid_write_mutex);
	closure_init(cl, parent);

	for (i = 0; i < KEY_PTRS(k); i++) {
		struct bio *bio = bch_bbio_alloc(c);

		bio->bi_opf = REQ_SYNC | REQ_META | op_flags;
		bio->bi_iter.bi_size = KEY_SIZE(k) << 9;

		bio->bi_end_io	= uuid_endio;
		bio->bi_private = cl;
		bio_set_op_attrs(bio, op, REQ_SYNC|REQ_META|op_flags);
		bch_bio_map(bio, c->uuids);

		bch_submit_bbio(bio, c, k, i);

		if (op != REQ_OP_WRITE)
			break;
	}

	bch_extent_to_text(buf, sizeof(buf), k);
	pr_debug("%s UUIDs at %s", op == REQ_OP_WRITE ? "wrote" : "read", buf);

	for (u = c->uuids; u < c->uuids + c->nr_uuids; u++)
		if (!bch_is_zero(u->uuid, 16))
			pr_debug("Slot %zi: %pU: %s: 1st: %u last: %u inv: %u",
				 u - c->uuids, u->uuid, u->label,
				 u->first_reg, u->last_reg, u->invalidated);

	closure_return_with_destructor(cl, uuid_io_unlock);
}
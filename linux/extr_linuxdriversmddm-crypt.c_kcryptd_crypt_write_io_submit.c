#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct TYPE_7__ {int /*<<< orphan*/  bi_size; } ;
struct TYPE_8__ {TYPE_1__ iter_out; struct bio* bio_out; } ;
struct dm_crypt_io {scalar_t__ sector; int /*<<< orphan*/  rb_node; TYPE_2__ ctx; int /*<<< orphan*/  error; struct crypt_config* cc; } ;
struct TYPE_10__ {struct rb_node* rb_node; } ;
struct crypt_config {scalar_t__ start; int /*<<< orphan*/  write_thread_lock; TYPE_4__ write_tree; int /*<<< orphan*/  write_thread; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_3__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_11__ {scalar_t__ sector; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM_CRYPT_NO_OFFLOAD ; 
 scalar_t__ RB_EMPTY_ROOT (TYPE_4__*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  crypt_dec_pending (struct dm_crypt_io*) ; 
 int /*<<< orphan*/  crypt_free_buffer_pages (struct crypt_config*,struct bio*) ; 
 TYPE_5__* crypt_io_from_node (struct rb_node*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rb_insert_color (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kcryptd_crypt_write_io_submit(struct dm_crypt_io *io, int async)
{
	struct bio *clone = io->ctx.bio_out;
	struct crypt_config *cc = io->cc;
	unsigned long flags;
	sector_t sector;
	struct rb_node **rbp, *parent;

	if (unlikely(io->error)) {
		crypt_free_buffer_pages(cc, clone);
		bio_put(clone);
		crypt_dec_pending(io);
		return;
	}

	/* crypt_convert should have filled the clone bio */
	BUG_ON(io->ctx.iter_out.bi_size);

	clone->bi_iter.bi_sector = cc->start + io->sector;

	if (likely(!async) && test_bit(DM_CRYPT_NO_OFFLOAD, &cc->flags)) {
		generic_make_request(clone);
		return;
	}

	spin_lock_irqsave(&cc->write_thread_lock, flags);
	if (RB_EMPTY_ROOT(&cc->write_tree))
		wake_up_process(cc->write_thread);
	rbp = &cc->write_tree.rb_node;
	parent = NULL;
	sector = io->sector;
	while (*rbp) {
		parent = *rbp;
		if (sector < crypt_io_from_node(parent)->sector)
			rbp = &(*rbp)->rb_left;
		else
			rbp = &(*rbp)->rb_right;
	}
	rb_link_node(&io->rb_node, parent, rbp);
	rb_insert_color(&io->rb_node, &cc->write_tree);
	spin_unlock_irqrestore(&cc->write_thread_lock, flags);
}
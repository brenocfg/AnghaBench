#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct frame {scalar_t__ current_child; scalar_t__ nr_children; TYPE_3__* n; scalar_t__ level; } ;
struct TYPE_6__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* dec ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dm_btree_info {TYPE_2__ value_type; int /*<<< orphan*/  tm; } ;
struct del_stack {int top; int /*<<< orphan*/  tm; struct dm_btree_info* info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {TYPE_1__ header; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int INTERNAL_NODE ; 
 scalar_t__ is_internal_level (struct dm_btree_info*,struct frame*) ; 
 int /*<<< orphan*/  kfree (struct del_stack*) ; 
 struct del_stack* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_frame (struct del_stack*) ; 
 int push_frame (struct del_stack*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int top_frame (struct del_stack*,struct frame**) ; 
 int /*<<< orphan*/  unlock_all_frames (struct del_stack*) ; 
 scalar_t__ unprocessed_frames (struct del_stack*) ; 
 int /*<<< orphan*/  value64 (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  value_ptr (TYPE_3__*,unsigned int) ; 

int dm_btree_del(struct dm_btree_info *info, dm_block_t root)
{
	int r;
	struct del_stack *s;

	/*
	 * dm_btree_del() is called via an ioctl, as such should be
	 * considered an FS op.  We can't recurse back into the FS, so we
	 * allocate GFP_NOFS.
	 */
	s = kmalloc(sizeof(*s), GFP_NOFS);
	if (!s)
		return -ENOMEM;
	s->info = info;
	s->tm = info->tm;
	s->top = -1;

	r = push_frame(s, root, 0);
	if (r)
		goto out;

	while (unprocessed_frames(s)) {
		uint32_t flags;
		struct frame *f;
		dm_block_t b;

		r = top_frame(s, &f);
		if (r)
			goto out;

		if (f->current_child >= f->nr_children) {
			pop_frame(s);
			continue;
		}

		flags = le32_to_cpu(f->n->header.flags);
		if (flags & INTERNAL_NODE) {
			b = value64(f->n, f->current_child);
			f->current_child++;
			r = push_frame(s, b, f->level);
			if (r)
				goto out;

		} else if (is_internal_level(info, f)) {
			b = value64(f->n, f->current_child);
			f->current_child++;
			r = push_frame(s, b, f->level + 1);
			if (r)
				goto out;

		} else {
			if (info->value_type.dec) {
				unsigned i;

				for (i = 0; i < f->nr_children; i++)
					info->value_type.dec(info->value_type.context,
							     value_ptr(f->n, i));
			}
			pop_frame(s);
		}
	}
out:
	if (r) {
		/* cleanup all frames of del_stack */
		unlock_all_frames(s);
	}
	kfree(s);

	return r;
}
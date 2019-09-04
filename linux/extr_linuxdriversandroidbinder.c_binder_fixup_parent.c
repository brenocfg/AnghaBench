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
typedef  int /*<<< orphan*/  u8 ;
struct binder_transaction {struct binder_proc* to_proc; struct binder_buffer* buffer; } ;
struct binder_thread {int /*<<< orphan*/  pid; struct binder_proc* proc; } ;
struct binder_proc {int /*<<< orphan*/  alloc; int /*<<< orphan*/  pid; } ;
struct binder_buffer_object {int flags; int parent_offset; int length; scalar_t__ buffer; int /*<<< orphan*/  parent; } ;
struct binder_buffer {int dummy; } ;
typedef  scalar_t__ binder_uintptr_t ;
typedef  int /*<<< orphan*/  binder_size_t ;

/* Variables and functions */
 int BINDER_BUFFER_FLAG_HAS_PARENT ; 
 int EINVAL ; 
 uintptr_t binder_alloc_get_user_buffer_offset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_user_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_validate_fixup (struct binder_buffer*,int /*<<< orphan*/ *,struct binder_buffer_object*,int,struct binder_buffer_object*,int /*<<< orphan*/ ) ; 
 struct binder_buffer_object* binder_validate_ptr (struct binder_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int binder_fixup_parent(struct binder_transaction *t,
			       struct binder_thread *thread,
			       struct binder_buffer_object *bp,
			       binder_size_t *off_start,
			       binder_size_t num_valid,
			       struct binder_buffer_object *last_fixup_obj,
			       binder_size_t last_fixup_min_off)
{
	struct binder_buffer_object *parent;
	u8 *parent_buffer;
	struct binder_buffer *b = t->buffer;
	struct binder_proc *proc = thread->proc;
	struct binder_proc *target_proc = t->to_proc;

	if (!(bp->flags & BINDER_BUFFER_FLAG_HAS_PARENT))
		return 0;

	parent = binder_validate_ptr(b, bp->parent, off_start, num_valid);
	if (!parent) {
		binder_user_error("%d:%d got transaction with invalid parent offset or type\n",
				  proc->pid, thread->pid);
		return -EINVAL;
	}

	if (!binder_validate_fixup(b, off_start,
				   parent, bp->parent_offset,
				   last_fixup_obj,
				   last_fixup_min_off)) {
		binder_user_error("%d:%d got transaction with out-of-order buffer fixup\n",
				  proc->pid, thread->pid);
		return -EINVAL;
	}

	if (parent->length < sizeof(binder_uintptr_t) ||
	    bp->parent_offset > parent->length - sizeof(binder_uintptr_t)) {
		/* No space for a pointer here! */
		binder_user_error("%d:%d got transaction with invalid parent offset\n",
				  proc->pid, thread->pid);
		return -EINVAL;
	}
	parent_buffer = (u8 *)((uintptr_t)parent->buffer -
			binder_alloc_get_user_buffer_offset(
				&target_proc->alloc));
	*(binder_uintptr_t *)(parent_buffer + bp->parent_offset) = bp->buffer;

	return 0;
}
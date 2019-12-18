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
struct rb_root {int /*<<< orphan*/  rb_node; } ;
struct dm_crypt_io {int /*<<< orphan*/  rb_node; } ;
struct crypt_config {int /*<<< orphan*/  write_thread_lock; struct rb_root write_tree; } ;
struct blk_plug {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (struct rb_root*) ; 
 struct rb_root RB_ROOT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 struct dm_crypt_io* crypt_io_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcryptd_io_write (struct dm_crypt_io*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,struct rb_root*) ; 
 int /*<<< orphan*/  rb_first (struct rb_root*) ; 
 int /*<<< orphan*/  rb_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmcrypt_write(void *data)
{
	struct crypt_config *cc = data;
	struct dm_crypt_io *io;

	while (1) {
		struct rb_root write_tree;
		struct blk_plug plug;

		spin_lock_irq(&cc->write_thread_lock);
continue_locked:

		if (!RB_EMPTY_ROOT(&cc->write_tree))
			goto pop_from_list;

		set_current_state(TASK_INTERRUPTIBLE);

		spin_unlock_irq(&cc->write_thread_lock);

		if (unlikely(kthread_should_stop())) {
			set_current_state(TASK_RUNNING);
			break;
		}

		schedule();

		set_current_state(TASK_RUNNING);
		spin_lock_irq(&cc->write_thread_lock);
		goto continue_locked;

pop_from_list:
		write_tree = cc->write_tree;
		cc->write_tree = RB_ROOT;
		spin_unlock_irq(&cc->write_thread_lock);

		BUG_ON(rb_parent(write_tree.rb_node));

		/*
		 * Note: we cannot walk the tree here with rb_next because
		 * the structures may be freed when kcryptd_io_write is called.
		 */
		blk_start_plug(&plug);
		do {
			io = crypt_io_from_node(rb_first(&write_tree));
			rb_erase(&io->rb_node, &write_tree);
			kcryptd_io_write(io);
		} while (!RB_EMPTY_ROOT(&write_tree));
		blk_finish_plug(&plug);
	}
	return 0;
}
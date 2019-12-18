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
struct tty_struct {int index; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; int /*<<< orphan*/  ops; struct tty_driver* driver; int /*<<< orphan*/  SAK_work; int /*<<< orphan*/  tty_files; int /*<<< orphan*/  files_lock; int /*<<< orphan*/  flow_lock; int /*<<< orphan*/  ctrl_lock; int /*<<< orphan*/  atomic_write_lock; int /*<<< orphan*/  hangup_work; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  ldisc_sem; int /*<<< orphan*/  winsize_mutex; int /*<<< orphan*/  termios_rwsem; int /*<<< orphan*/  throttle_mutex; int /*<<< orphan*/  legacy_mutex; int /*<<< orphan*/ * pgrp; int /*<<< orphan*/ * session; int /*<<< orphan*/  magic; int /*<<< orphan*/  kref; } ;
struct tty_driver {int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTY_MAGIC ; 
 int /*<<< orphan*/  do_SAK_work ; 
 int /*<<< orphan*/  do_tty_hangup ; 
 int /*<<< orphan*/  init_ldsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tty_struct*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct tty_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_get_device (struct tty_struct*) ; 
 scalar_t__ tty_ldisc_init (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_line_name (struct tty_driver*,int,int /*<<< orphan*/ ) ; 

struct tty_struct *alloc_tty_struct(struct tty_driver *driver, int idx)
{
	struct tty_struct *tty;

	tty = kzalloc(sizeof(*tty), GFP_KERNEL);
	if (!tty)
		return NULL;

	kref_init(&tty->kref);
	tty->magic = TTY_MAGIC;
	if (tty_ldisc_init(tty)) {
		kfree(tty);
		return NULL;
	}
	tty->session = NULL;
	tty->pgrp = NULL;
	mutex_init(&tty->legacy_mutex);
	mutex_init(&tty->throttle_mutex);
	init_rwsem(&tty->termios_rwsem);
	mutex_init(&tty->winsize_mutex);
	init_ldsem(&tty->ldisc_sem);
	init_waitqueue_head(&tty->write_wait);
	init_waitqueue_head(&tty->read_wait);
	INIT_WORK(&tty->hangup_work, do_tty_hangup);
	mutex_init(&tty->atomic_write_lock);
	spin_lock_init(&tty->ctrl_lock);
	spin_lock_init(&tty->flow_lock);
	spin_lock_init(&tty->files_lock);
	INIT_LIST_HEAD(&tty->tty_files);
	INIT_WORK(&tty->SAK_work, do_SAK_work);

	tty->driver = driver;
	tty->ops = driver->ops;
	tty->index = idx;
	tty_line_name(driver, idx, tty->name);
	tty->dev = tty_get_device(tty);

	return tty;
}
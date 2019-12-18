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
struct tty_struct {TYPE_1__* ops; struct n_tty_data* disc_data; } ;
struct n_tty_data {size_t echo_head; size_t echo_mark; size_t echo_commit; size_t echo_tail; int /*<<< orphan*/  output_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_chars ) (struct tty_struct*) ;} ;

/* Variables and functions */
 size_t ECHO_BLOCK ; 
 size_t ECHO_COMMIT_WATERMARK ; 
 size_t __process_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 

__attribute__((used)) static void commit_echoes(struct tty_struct *tty)
{
	struct n_tty_data *ldata = tty->disc_data;
	size_t nr, old, echoed;
	size_t head;

	mutex_lock(&ldata->output_lock);
	head = ldata->echo_head;
	ldata->echo_mark = head;
	old = ldata->echo_commit - ldata->echo_tail;

	/* Process committed echoes if the accumulated # of bytes
	 * is over the threshold (and try again each time another
	 * block is accumulated) */
	nr = head - ldata->echo_tail;
	if (nr < ECHO_COMMIT_WATERMARK ||
	    (nr % ECHO_BLOCK > old % ECHO_BLOCK)) {
		mutex_unlock(&ldata->output_lock);
		return;
	}

	ldata->echo_commit = head;
	echoed = __process_echoes(tty);
	mutex_unlock(&ldata->output_lock);

	if (echoed && tty->ops->flush_chars)
		tty->ops->flush_chars(tty);
}
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
struct winsize {int dummy; } ;
struct tty_struct {int /*<<< orphan*/  winsize_mutex; struct winsize winsize; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  kill_pgrp (struct pid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcmp (struct winsize*,struct winsize*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 struct pid* tty_get_pgrp (struct tty_struct*) ; 

int tty_do_resize(struct tty_struct *tty, struct winsize *ws)
{
	struct pid *pgrp;

	/* Lock the tty */
	mutex_lock(&tty->winsize_mutex);
	if (!memcmp(ws, &tty->winsize, sizeof(*ws)))
		goto done;

	/* Signal the foreground process group */
	pgrp = tty_get_pgrp(tty);
	if (pgrp)
		kill_pgrp(pgrp, SIGWINCH, 1);
	put_pid(pgrp);

	tty->winsize = *ws;
done:
	mutex_unlock(&tty->winsize_mutex);
	return 0;
}
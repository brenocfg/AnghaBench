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
struct tty_struct {int /*<<< orphan*/  flow_stopped; scalar_t__ stopped; struct n_tty_data* disc_data; } ;
struct n_tty_data {scalar_t__ canon_head; scalar_t__ read_head; } ;

/* Variables and functions */
 scalar_t__ I_IXANY (struct tty_struct*) ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 scalar_t__ L_ECHO (struct tty_struct*) ; 
 int /*<<< orphan*/  commit_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  echo_char (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  echo_set_canon_col (struct n_tty_data*) ; 
 int /*<<< orphan*/  finish_erasing (struct n_tty_data*) ; 
 int /*<<< orphan*/  process_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  put_tty_queue (unsigned char,struct n_tty_data*) ; 
 int /*<<< orphan*/  start_tty (struct tty_struct*) ; 

__attribute__((used)) static inline void
n_tty_receive_char_fast(struct tty_struct *tty, unsigned char c)
{
	struct n_tty_data *ldata = tty->disc_data;

	if (tty->stopped && !tty->flow_stopped && I_IXON(tty) && I_IXANY(tty)) {
		start_tty(tty);
		process_echoes(tty);
	}
	if (L_ECHO(tty)) {
		finish_erasing(ldata);
		/* Record the column of first canon char. */
		if (ldata->canon_head == ldata->read_head)
			echo_set_canon_col(ldata);
		echo_char(c, tty);
		commit_echoes(tty);
	}
	put_tty_queue(c, ldata);
}
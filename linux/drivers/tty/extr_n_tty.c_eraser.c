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
struct tty_struct {struct n_tty_data* disc_data; } ;
struct n_tty_data {size_t read_head; size_t canon_head; int erasing; } ;

/* Variables and functions */
 unsigned char ERASE_CHAR (struct tty_struct*) ; 
 unsigned char KILL_CHAR (struct tty_struct*) ; 
 scalar_t__ L_ECHO (struct tty_struct*) ; 
 scalar_t__ L_ECHOCTL (struct tty_struct*) ; 
 int /*<<< orphan*/  L_ECHOE (struct tty_struct*) ; 
 scalar_t__ L_ECHOK (struct tty_struct*) ; 
 int /*<<< orphan*/  L_ECHOKE (struct tty_struct*) ; 
 scalar_t__ L_ECHOPRT (struct tty_struct*) ; 
 scalar_t__ MASK (size_t) ; 
 unsigned char WERASE_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  echo_char (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  echo_char_raw (char,struct n_tty_data*) ; 
 int /*<<< orphan*/  echo_erase_tab (unsigned int,int,struct n_tty_data*) ; 
 int /*<<< orphan*/  echo_move_back_col (struct n_tty_data*) ; 
 int /*<<< orphan*/  finish_erasing (struct n_tty_data*) ; 
 scalar_t__ is_continuation (unsigned char,struct tty_struct*) ; 
 scalar_t__ isalnum (unsigned char) ; 
 scalar_t__ iscntrl (unsigned char) ; 
 char read_buf (struct n_tty_data*,size_t) ; 

__attribute__((used)) static void eraser(unsigned char c, struct tty_struct *tty)
{
	struct n_tty_data *ldata = tty->disc_data;
	enum { ERASE, WERASE, KILL } kill_type;
	size_t head;
	size_t cnt;
	int seen_alnums;

	if (ldata->read_head == ldata->canon_head) {
		/* process_output('\a', tty); */ /* what do you think? */
		return;
	}
	if (c == ERASE_CHAR(tty))
		kill_type = ERASE;
	else if (c == WERASE_CHAR(tty))
		kill_type = WERASE;
	else {
		if (!L_ECHO(tty)) {
			ldata->read_head = ldata->canon_head;
			return;
		}
		if (!L_ECHOK(tty) || !L_ECHOKE(tty) || !L_ECHOE(tty)) {
			ldata->read_head = ldata->canon_head;
			finish_erasing(ldata);
			echo_char(KILL_CHAR(tty), tty);
			/* Add a newline if ECHOK is on and ECHOKE is off. */
			if (L_ECHOK(tty))
				echo_char_raw('\n', ldata);
			return;
		}
		kill_type = KILL;
	}

	seen_alnums = 0;
	while (MASK(ldata->read_head) != MASK(ldata->canon_head)) {
		head = ldata->read_head;

		/* erase a single possibly multibyte character */
		do {
			head--;
			c = read_buf(ldata, head);
		} while (is_continuation(c, tty) &&
			 MASK(head) != MASK(ldata->canon_head));

		/* do not partially erase */
		if (is_continuation(c, tty))
			break;

		if (kill_type == WERASE) {
			/* Equivalent to BSD's ALTWERASE. */
			if (isalnum(c) || c == '_')
				seen_alnums++;
			else if (seen_alnums)
				break;
		}
		cnt = ldata->read_head - head;
		ldata->read_head = head;
		if (L_ECHO(tty)) {
			if (L_ECHOPRT(tty)) {
				if (!ldata->erasing) {
					echo_char_raw('\\', ldata);
					ldata->erasing = 1;
				}
				/* if cnt > 1, output a multi-byte character */
				echo_char(c, tty);
				while (--cnt > 0) {
					head++;
					echo_char_raw(read_buf(ldata, head), ldata);
					echo_move_back_col(ldata);
				}
			} else if (kill_type == ERASE && !L_ECHOE(tty)) {
				echo_char(ERASE_CHAR(tty), tty);
			} else if (c == '\t') {
				unsigned int num_chars = 0;
				int after_tab = 0;
				size_t tail = ldata->read_head;

				/*
				 * Count the columns used for characters
				 * since the start of input or after a
				 * previous tab.
				 * This info is used to go back the correct
				 * number of columns.
				 */
				while (MASK(tail) != MASK(ldata->canon_head)) {
					tail--;
					c = read_buf(ldata, tail);
					if (c == '\t') {
						after_tab = 1;
						break;
					} else if (iscntrl(c)) {
						if (L_ECHOCTL(tty))
							num_chars += 2;
					} else if (!is_continuation(c, tty)) {
						num_chars++;
					}
				}
				echo_erase_tab(num_chars, after_tab, ldata);
			} else {
				if (iscntrl(c) && L_ECHOCTL(tty)) {
					echo_char_raw('\b', ldata);
					echo_char_raw(' ', ldata);
					echo_char_raw('\b', ldata);
				}
				if (!iscntrl(c) || L_ECHOCTL(tty)) {
					echo_char_raw('\b', ldata);
					echo_char_raw(' ', ldata);
					echo_char_raw('\b', ldata);
				}
			}
		}
		if (kill_type == ERASE)
			break;
	}
	if (ldata->read_head == ldata->canon_head && L_ECHO(tty))
		finish_erasing(ldata);
}
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
struct n_tty_data {int dummy; } ;

/* Variables and functions */
 char TTY_NORMAL ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  n_tty_receive_char_flagged (struct tty_struct*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  put_tty_queue (int /*<<< orphan*/ ,struct n_tty_data*) ; 

__attribute__((used)) static void
n_tty_receive_buf_raw(struct tty_struct *tty, const unsigned char *cp,
		      char *fp, int count)
{
	struct n_tty_data *ldata = tty->disc_data;
	char flag = TTY_NORMAL;

	while (count--) {
		if (fp)
			flag = *fp++;
		if (likely(flag == TTY_NORMAL))
			put_tty_queue(*cp++, ldata);
		else
			n_tty_receive_char_flagged(tty, *cp++, flag);
	}
}
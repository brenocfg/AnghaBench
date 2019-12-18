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
struct n_tty_data {int /*<<< orphan*/  char_map; } ;

/* Variables and functions */
 scalar_t__ I_ISTRIP (struct tty_struct*) ; 
 scalar_t__ I_IUCLC (struct tty_struct*) ; 
 scalar_t__ L_EXTPROC (struct tty_struct*) ; 
 scalar_t__ L_IEXTEN (struct tty_struct*) ; 
 char TTY_NORMAL ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  n_tty_receive_char_flagged (struct tty_struct*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  n_tty_receive_char_inline (struct tty_struct*,unsigned char) ; 
 int /*<<< orphan*/  n_tty_receive_char_lnext (struct tty_struct*,int /*<<< orphan*/ ,char) ; 
 scalar_t__ n_tty_receive_char_special (struct tty_struct*,unsigned char) ; 
 int /*<<< orphan*/  put_tty_queue (unsigned char,struct n_tty_data*) ; 
 int /*<<< orphan*/  test_bit (unsigned char,int /*<<< orphan*/ ) ; 
 unsigned char tolower (unsigned char) ; 

__attribute__((used)) static void
n_tty_receive_buf_standard(struct tty_struct *tty, const unsigned char *cp,
			  char *fp, int count)
{
	struct n_tty_data *ldata = tty->disc_data;
	char flag = TTY_NORMAL;

	while (count--) {
		if (fp)
			flag = *fp++;
		if (likely(flag == TTY_NORMAL)) {
			unsigned char c = *cp++;

			if (I_ISTRIP(tty))
				c &= 0x7f;
			if (I_IUCLC(tty) && L_IEXTEN(tty))
				c = tolower(c);
			if (L_EXTPROC(tty)) {
				put_tty_queue(c, ldata);
				continue;
			}
			if (!test_bit(c, ldata->char_map))
				n_tty_receive_char_inline(tty, c);
			else if (n_tty_receive_char_special(tty, c) && count) {
				if (fp)
					flag = *fp++;
				n_tty_receive_char_lnext(tty, *cp++, flag);
				count--;
			}
		} else
			n_tty_receive_char_flagged(tty, *cp++, flag);
	}
}
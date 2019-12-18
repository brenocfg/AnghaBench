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
struct tty_struct {int /*<<< orphan*/  read_wait; int /*<<< orphan*/  fasync; TYPE_1__* ops; scalar_t__ closing; struct n_tty_data* disc_data; } ;
struct n_tty_data {int /*<<< orphan*/  read_head; int /*<<< orphan*/  commit_head; scalar_t__ icanon; scalar_t__ lnext; scalar_t__ raw; scalar_t__ real_raw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_chars ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 scalar_t__ I_ISTRIP (struct tty_struct*) ; 
 scalar_t__ I_IUCLC (struct tty_struct*) ; 
 int /*<<< orphan*/  I_PARMRK (struct tty_struct*) ; 
 scalar_t__ L_EXTPROC (struct tty_struct*) ; 
 scalar_t__ L_IEXTEN (struct tty_struct*) ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 char TTY_NORMAL ; 
 int /*<<< orphan*/  flush_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_tty_receive_buf_closing (struct tty_struct*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  n_tty_receive_buf_fast (struct tty_struct*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  n_tty_receive_buf_raw (struct tty_struct*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  n_tty_receive_buf_real_raw (struct tty_struct*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  n_tty_receive_buf_standard (struct tty_struct*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  n_tty_receive_char_lnext (struct tty_struct*,int /*<<< orphan*/ ,char) ; 
 scalar_t__ read_cnt (struct n_tty_data*) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __receive_buf(struct tty_struct *tty, const unsigned char *cp,
			  char *fp, int count)
{
	struct n_tty_data *ldata = tty->disc_data;
	bool preops = I_ISTRIP(tty) || (I_IUCLC(tty) && L_IEXTEN(tty));

	if (ldata->real_raw)
		n_tty_receive_buf_real_raw(tty, cp, fp, count);
	else if (ldata->raw || (L_EXTPROC(tty) && !preops))
		n_tty_receive_buf_raw(tty, cp, fp, count);
	else if (tty->closing && !L_EXTPROC(tty))
		n_tty_receive_buf_closing(tty, cp, fp, count);
	else {
		if (ldata->lnext) {
			char flag = TTY_NORMAL;

			if (fp)
				flag = *fp++;
			n_tty_receive_char_lnext(tty, *cp++, flag);
			count--;
		}

		if (!preops && !I_PARMRK(tty))
			n_tty_receive_buf_fast(tty, cp, fp, count);
		else
			n_tty_receive_buf_standard(tty, cp, fp, count);

		flush_echoes(tty);
		if (tty->ops->flush_chars)
			tty->ops->flush_chars(tty);
	}

	if (ldata->icanon && !L_EXTPROC(tty))
		return;

	/* publish read_head to consumer */
	smp_store_release(&ldata->commit_head, ldata->read_head);

	if (read_cnt(ldata)) {
		kill_fasync(&tty->fasync, SIGIO, POLL_IN);
		wake_up_interruptible_poll(&tty->read_wait, EPOLLIN);
	}
}
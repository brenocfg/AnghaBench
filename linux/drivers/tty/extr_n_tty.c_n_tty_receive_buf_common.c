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
struct tty_struct {int receive_room; int /*<<< orphan*/  termios_rwsem; TYPE_1__* driver; int /*<<< orphan*/  flags; struct n_tty_data* disc_data; } ;
struct n_tty_data {size_t read_head; size_t canon_head; int no_room; scalar_t__ icanon; int /*<<< orphan*/  read_tail; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 size_t N_TTY_BUF_SIZE ; 
 scalar_t__ TTY_DRIVER_TYPE_PTY ; 
 int /*<<< orphan*/  TTY_LDISC_CHANGING ; 
 char TTY_PARITY ; 
 int /*<<< orphan*/  TTY_UNTHROTTLE_SAFE ; 
 int /*<<< orphan*/  __receive_buf (struct tty_struct*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  __tty_set_flow_change (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  n_tty_check_throttle (struct tty_struct*) ; 
 size_t smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_set_flow_change (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_unthrottle_safe (struct tty_struct*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
n_tty_receive_buf_common(struct tty_struct *tty, const unsigned char *cp,
			 char *fp, int count, int flow)
{
	struct n_tty_data *ldata = tty->disc_data;
	int room, n, rcvd = 0, overflow;

	down_read(&tty->termios_rwsem);

	do {
		/*
		 * When PARMRK is set, each input char may take up to 3 chars
		 * in the read buf; reduce the buffer space avail by 3x
		 *
		 * If we are doing input canonicalization, and there are no
		 * pending newlines, let characters through without limit, so
		 * that erase characters will be handled.  Other excess
		 * characters will be beeped.
		 *
		 * paired with store in *_copy_from_read_buf() -- guarantees
		 * the consumer has loaded the data in read_buf up to the new
		 * read_tail (so this producer will not overwrite unread data)
		 */
		size_t tail = smp_load_acquire(&ldata->read_tail);

		room = N_TTY_BUF_SIZE - (ldata->read_head - tail);
		if (I_PARMRK(tty))
			room = (room + 2) / 3;
		room--;
		if (room <= 0) {
			overflow = ldata->icanon && ldata->canon_head == tail;
			if (overflow && room < 0)
				ldata->read_head--;
			room = overflow;
			ldata->no_room = flow && !room;
		} else
			overflow = 0;

		n = min(count, room);
		if (!n)
			break;

		/* ignore parity errors if handling overflow */
		if (!overflow || !fp || *fp != TTY_PARITY)
			__receive_buf(tty, cp, fp, n);

		cp += n;
		if (fp)
			fp += n;
		count -= n;
		rcvd += n;
	} while (!test_bit(TTY_LDISC_CHANGING, &tty->flags));

	tty->receive_room = room;

	/* Unthrottle if handling overflow on pty */
	if (tty->driver->type == TTY_DRIVER_TYPE_PTY) {
		if (overflow) {
			tty_set_flow_change(tty, TTY_UNTHROTTLE_SAFE);
			tty_unthrottle_safe(tty);
			__tty_set_flow_change(tty, 0);
		}
	} else
		n_tty_check_throttle(tty);

	up_read(&tty->termios_rwsem);

	return rcvd;
}
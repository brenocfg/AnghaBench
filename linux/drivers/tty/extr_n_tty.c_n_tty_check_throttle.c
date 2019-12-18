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
struct n_tty_data {scalar_t__ canon_head; scalar_t__ read_tail; scalar_t__ icanon; } ;

/* Variables and functions */
 scalar_t__ N_TTY_BUF_SIZE ; 
 scalar_t__ TTY_THRESHOLD_THROTTLE ; 
 int /*<<< orphan*/  TTY_THROTTLE_SAFE ; 
 int /*<<< orphan*/  __tty_set_flow_change (struct tty_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_cnt (struct n_tty_data*) ; 
 int /*<<< orphan*/  tty_set_flow_change (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int tty_throttle_safe (struct tty_struct*) ; 

__attribute__((used)) static void n_tty_check_throttle(struct tty_struct *tty)
{
	struct n_tty_data *ldata = tty->disc_data;

	/*
	 * Check the remaining room for the input canonicalization
	 * mode.  We don't want to throttle the driver if we're in
	 * canonical mode and don't have a newline yet!
	 */
	if (ldata->icanon && ldata->canon_head == ldata->read_tail)
		return;

	while (1) {
		int throttled;
		tty_set_flow_change(tty, TTY_THROTTLE_SAFE);
		if (N_TTY_BUF_SIZE - read_cnt(ldata) >= TTY_THRESHOLD_THROTTLE)
			break;
		throttled = tty_throttle_safe(tty);
		if (!throttled)
			break;
	}
	__tty_set_flow_change(tty, 0);
}
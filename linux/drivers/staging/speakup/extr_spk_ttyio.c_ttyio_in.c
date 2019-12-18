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
struct spk_ldisc_data {char buf; int buf_free; int /*<<< orphan*/  completion; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; struct spk_ldisc_data* disc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 TYPE_1__* speakup_tty ; 
 int /*<<< orphan*/  tty_schedule_flip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char ttyio_in(int timeout)
{
	struct spk_ldisc_data *ldisc_data = speakup_tty->disc_data;
	char rv;

	if (wait_for_completion_timeout(&ldisc_data->completion,
					usecs_to_jiffies(timeout)) == 0) {
		if (timeout)
			pr_warn("spk_ttyio: timeout (%d)  while waiting for input\n",
				timeout);
		return 0xff;
	}

	rv = ldisc_data->buf;
	/* Make sure we have read buf before we set buf_free to let
	 * the producer overwrite it
	 */
	mb();
	ldisc_data->buf_free = true;
	/* Let TTY push more characters */
	tty_schedule_flip(speakup_tty->port);

	return rv;
}
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
struct tty_struct {struct spk_ldisc_data* disc_data; } ;
struct spk_ldisc_data {int buf_free; unsigned char buf; int /*<<< orphan*/  completion; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_buff_add ) (unsigned char const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 TYPE_1__* spk_ttyio_synth ; 
 int /*<<< orphan*/  stub1 (unsigned char const) ; 

__attribute__((used)) static int spk_ttyio_receive_buf2(struct tty_struct *tty,
				  const unsigned char *cp, char *fp, int count)
{
	struct spk_ldisc_data *ldisc_data = tty->disc_data;

	if (spk_ttyio_synth->read_buff_add) {
		int i;

		for (i = 0; i < count; i++)
			spk_ttyio_synth->read_buff_add(cp[i]);

		return count;
	}

	if (!ldisc_data->buf_free)
		/* ttyio_in will tty_schedule_flip */
		return 0;

	/* Make sure the consumer has read buf before we have seen
	 * buf_free == true and overwrite buf
	 */
	mb();

	ldisc_data->buf = cp[0];
	ldisc_data->buf_free = false;
	complete(&ldisc_data->completion);

	return 1;
}
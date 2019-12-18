#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct tty_struct {int dummy; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct hvcs_struct {int todo_mask; int /*<<< orphan*/  chars_in_buffer; int /*<<< orphan*/ * buffer; TYPE_2__ port; TYPE_1__* vdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 int HVCS_TRY_WRITE ; 
 int hvc_put_chars (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void hvcs_try_write(struct hvcs_struct *hvcsd)
{
	uint32_t unit_address = hvcsd->vdev->unit_address;
	struct tty_struct *tty = hvcsd->port.tty;
	int sent;

	if (hvcsd->todo_mask & HVCS_TRY_WRITE) {
		/* won't send partial writes */
		sent = hvc_put_chars(unit_address,
				&hvcsd->buffer[0],
				hvcsd->chars_in_buffer );
		if (sent > 0) {
			hvcsd->chars_in_buffer = 0;
			/* wmb(); */
			hvcsd->todo_mask &= ~(HVCS_TRY_WRITE);
			/* wmb(); */

			/*
			 * We are still obligated to deliver the data to the
			 * hypervisor even if the tty has been closed because
			 * we committed to delivering it.  But don't try to wake
			 * a non-existent tty.
			 */
			if (tty) {
				tty_wakeup(tty);
			}
		}
	}
}
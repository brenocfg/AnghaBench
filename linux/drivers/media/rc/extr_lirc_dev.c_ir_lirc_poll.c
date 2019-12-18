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
struct rc_dev {scalar_t__ driver_type; int /*<<< orphan*/  registered; } ;
struct poll_table_struct {int dummy; } ;
struct lirc_fh {scalar_t__ rec_mode; int /*<<< orphan*/  rawir; int /*<<< orphan*/  scancodes; int /*<<< orphan*/  wait_poll; struct rc_dev* rc; } ;
struct file {struct lirc_fh* private_data; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ LIRC_MODE_MODE2 ; 
 scalar_t__ LIRC_MODE_SCANCODE ; 
 scalar_t__ RC_DRIVER_IR_RAW_TX ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t ir_lirc_poll(struct file *file, struct poll_table_struct *wait)
{
	struct lirc_fh *fh = file->private_data;
	struct rc_dev *rcdev = fh->rc;
	__poll_t events = 0;

	poll_wait(file, &fh->wait_poll, wait);

	if (!rcdev->registered) {
		events = EPOLLHUP | EPOLLERR;
	} else if (rcdev->driver_type != RC_DRIVER_IR_RAW_TX) {
		if (fh->rec_mode == LIRC_MODE_SCANCODE &&
		    !kfifo_is_empty(&fh->scancodes))
			events = EPOLLIN | EPOLLRDNORM;

		if (fh->rec_mode == LIRC_MODE_MODE2 &&
		    !kfifo_is_empty(&fh->rawir))
			events = EPOLLIN | EPOLLRDNORM;
	}

	return events;
}
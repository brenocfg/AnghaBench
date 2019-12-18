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
struct tty_struct {struct acm* driver_data; } ;
struct serial_struct {int close_delay; int closing_wait; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  xmit_fifo_size; } ;
struct TYPE_3__ {int close_delay; int closing_wait; } ;
struct TYPE_4__ {int /*<<< orphan*/  dwDTERate; } ;
struct acm {TYPE_1__ port; TYPE_2__ line; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int ASYNC_CLOSING_WAIT_NONE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_serial_info(struct tty_struct *tty, struct serial_struct *ss)
{
	struct acm *acm = tty->driver_data;

	ss->xmit_fifo_size = acm->writesize;
	ss->baud_base = le32_to_cpu(acm->line.dwDTERate);
	ss->close_delay	= acm->port.close_delay / 10;
	ss->closing_wait = acm->port.closing_wait == ASYNC_CLOSING_WAIT_NONE ?
				ASYNC_CLOSING_WAIT_NONE :
				acm->port.closing_wait / 10;
	return 0;
}
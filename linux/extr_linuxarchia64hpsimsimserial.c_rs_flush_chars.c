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
struct tty_struct {scalar_t__ stopped; struct serial_state* driver_data; } ;
struct TYPE_2__ {scalar_t__ head; scalar_t__ tail; int /*<<< orphan*/  buf; } ;
struct serial_state {TYPE_1__ xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  transmit_chars (struct tty_struct*,struct serial_state*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_flush_chars(struct tty_struct *tty)
{
	struct serial_state *info = tty->driver_data;

	if (info->xmit.head == info->xmit.tail || tty->stopped ||
			!info->xmit.buf)
		return;

	transmit_chars(tty, info, NULL);
}
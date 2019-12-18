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
struct tty_struct {struct ipw_tty* driver_data; } ;
struct serial_struct {int baud_base; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct ipw_tty {int /*<<< orphan*/  index; TYPE_1__ port; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  PORT_UNKNOWN ; 

__attribute__((used)) static int ipwireless_get_serial_info(struct tty_struct *linux_tty,
				      struct serial_struct *ss)
{
	struct ipw_tty *tty = linux_tty->driver_data;

	if (!tty)
		return -ENODEV;

	if (!tty->port.count)
		return -EINVAL;

	ss->type = PORT_UNKNOWN;
	ss->line = tty->index;
	ss->baud_base = 115200;
	return 0;
}
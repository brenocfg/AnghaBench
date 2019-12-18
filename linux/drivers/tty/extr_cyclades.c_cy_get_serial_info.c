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
struct tty_struct {int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct serial_struct {int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  flags; int /*<<< orphan*/  irq; scalar_t__ port; scalar_t__ line; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  flags; } ;
struct cyclades_port {int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  baud; TYPE_1__ port; scalar_t__ line; struct cyclades_card* card; int /*<<< orphan*/  type; } ;
struct cyclades_card {int /*<<< orphan*/  irq; scalar_t__ first_line; } ;

/* Variables and functions */
 int ENODEV ; 
 struct cyclades_card* cy_card ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cy_get_serial_info(struct tty_struct *tty,
				struct serial_struct *ss)
{
	struct cyclades_port *info = tty->driver_data;
	struct cyclades_card *cinfo = info->card;

	if (serial_paranoia_check(info, tty->name, "cy_ioctl"))
		return -ENODEV;
	ss->type = info->type;
	ss->line = info->line;
	ss->port = (info->card - cy_card) * 0x100 + info->line -
			cinfo->first_line;
	ss->irq = cinfo->irq;
	ss->flags = info->port.flags;
	ss->close_delay = info->port.close_delay;
	ss->closing_wait = info->port.closing_wait;
	ss->baud_base = info->baud;
	ss->custom_divisor = info->custom_divisor;
	return 0;
}
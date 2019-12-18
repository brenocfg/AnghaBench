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
struct urb {int status; TYPE_2__* dev; struct moschip_port* context; } ;
struct moschip_port {TYPE_1__* port; scalar_t__ open; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  tty_port_tty_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mos7720_bulk_out_data_callback(struct urb *urb)
{
	struct moschip_port *mos7720_port;
	int status = urb->status;

	if (status) {
		dev_dbg(&urb->dev->dev, "nonzero write bulk status received:%d\n", status);
		return;
	}

	mos7720_port = urb->context;
	if (!mos7720_port) {
		dev_dbg(&urb->dev->dev, "NULL mos7720_port pointer\n");
		return ;
	}

	if (mos7720_port->open)
		tty_port_tty_wakeup(&mos7720_port->port->port);
}
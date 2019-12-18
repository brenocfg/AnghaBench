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
struct usb_serial_port {int /*<<< orphan*/  dev; } ;
struct moschip_port {int /*<<< orphan*/  DcrRegOffset; int /*<<< orphan*/  ControlRegOffset; int /*<<< orphan*/  SpRegOffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mos7840_dump_serial_port(struct usb_serial_port *port,
				     struct moschip_port *mos7840_port)
{

	dev_dbg(&port->dev, "SpRegOffset is %2x\n", mos7840_port->SpRegOffset);
	dev_dbg(&port->dev, "ControlRegOffset is %2x\n", mos7840_port->ControlRegOffset);
	dev_dbg(&port->dev, "DCRRegOffset is %2x\n", mos7840_port->DcrRegOffset);

}
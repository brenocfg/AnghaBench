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
struct port {scalar_t__ host_connected; int /*<<< orphan*/  guest_connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  port_has_data (struct port*) ; 

__attribute__((used)) static bool will_read_block(struct port *port)
{
	if (!port->guest_connected) {
		/* Port got hot-unplugged. Let's exit. */
		return false;
	}
	return !port_has_data(port) && port->host_connected;
}
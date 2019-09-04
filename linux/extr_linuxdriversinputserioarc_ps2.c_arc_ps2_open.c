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
struct serio {struct arc_ps2_port* port_data; } ;
struct arc_ps2_port {int /*<<< orphan*/  status_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS2_STAT_RX_INT_EN ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arc_ps2_open(struct serio *io)
{
	struct arc_ps2_port *port = io->port_data;

	iowrite32(PS2_STAT_RX_INT_EN, port->status_addr);

	return 0;
}
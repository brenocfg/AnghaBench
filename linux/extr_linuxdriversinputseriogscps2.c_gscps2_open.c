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
struct serio {struct gscps2port* port_data; } ;
struct gscps2port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  gscps2_enable (struct gscps2port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gscps2_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gscps2_reset (struct gscps2port*) ; 

__attribute__((used)) static int gscps2_open(struct serio *port)
{
	struct gscps2port *ps2port = port->port_data;

	gscps2_reset(ps2port);

	/* enable it */
	gscps2_enable(ps2port, ENABLE);

	gscps2_interrupt(0, NULL);

	return 0;
}
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
struct parport {int muxport; struct parport** slaves; struct parport* physport; int /*<<< orphan*/  portnum; int /*<<< orphan*/  ops; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct parport* parport_register_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct parport *clone_parport(struct parport *real, int muxport)
{
	struct parport *extra = parport_register_port(real->base,
						       real->irq,
						       real->dma,
						       real->ops);
	if (extra) {
		extra->portnum = real->portnum;
		extra->physport = real;
		extra->muxport = muxport;
		real->slaves[muxport-1] = extra;
	}

	return extra;
}
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
struct vio_completion {int err; int /*<<< orphan*/  com; int /*<<< orphan*/  waiting_for; } ;
struct TYPE_2__ {struct vio_completion* cmp; } ;
struct vdc_port {TYPE_1__ vio; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAITING_FOR_LINK_UP ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vio_port_up (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vdc_port_up(struct vdc_port *port)
{
	struct vio_completion comp;

	init_completion(&comp.com);
	comp.err = 0;
	comp.waiting_for = WAITING_FOR_LINK_UP;
	port->vio.cmp = &comp;

	vio_port_up(&port->vio);
	wait_for_completion(&comp.com);
	return comp.err;
}
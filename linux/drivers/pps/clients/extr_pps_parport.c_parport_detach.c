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
struct pps_client_pp {int /*<<< orphan*/  index; int /*<<< orphan*/  pps; } ;
struct parport {TYPE_1__* ops; struct pardevice* cad; } ;
struct pardevice {struct pps_client_pp* private; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_irq ) (struct parport*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pps_client_pp*) ; 
 int /*<<< orphan*/  parport_release (struct pardevice*) ; 
 int /*<<< orphan*/  parport_unregister_device (struct pardevice*) ; 
 int /*<<< orphan*/  pps_client_index ; 
 int /*<<< orphan*/  pps_unregister_source (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct parport*) ; 

__attribute__((used)) static void parport_detach(struct parport *port)
{
	struct pardevice *pardev = port->cad;
	struct pps_client_pp *device;

	/* FIXME: oooh, this is ugly! */
	if (!pardev || strcmp(pardev->name, KBUILD_MODNAME))
		/* not our port */
		return;

	device = pardev->private;

	port->ops->disable_irq(port);
	pps_unregister_source(device->pps);
	parport_release(pardev);
	parport_unregister_device(pardev);
	ida_simple_remove(&pps_client_index, device->index);
	kfree(device);
}
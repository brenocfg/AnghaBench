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
struct TYPE_2__ {size_t trtype; } ;
struct nvmet_port {int enabled; TYPE_1__ disc_addr; int /*<<< orphan*/ * tr_ops; } ;
struct nvmet_fabrics_ops {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* remove_port ) (struct nvmet_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_config_sem ; 
 struct nvmet_fabrics_ops** nvmet_transports ; 
 int /*<<< orphan*/  stub1 (struct nvmet_port*) ; 

void nvmet_disable_port(struct nvmet_port *port)
{
	const struct nvmet_fabrics_ops *ops;

	lockdep_assert_held(&nvmet_config_sem);

	port->enabled = false;
	port->tr_ops = NULL;

	ops = nvmet_transports[port->disc_addr.trtype];
	ops->remove_port(port);
	module_put(ops->owner);
}
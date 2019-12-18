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
struct nvmet_port {scalar_t__ inline_data_size; int enabled; struct nvmet_fabrics_ops const* tr_ops; TYPE_1__ disc_addr; } ;
struct nvmet_fabrics_ops {int (* add_port ) (struct nvmet_port*) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_config_sem ; 
 struct nvmet_fabrics_ops** nvmet_transports ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  request_module (char*,size_t) ; 
 int stub1 (struct nvmet_port*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nvmet_enable_port(struct nvmet_port *port)
{
	const struct nvmet_fabrics_ops *ops;
	int ret;

	lockdep_assert_held(&nvmet_config_sem);

	ops = nvmet_transports[port->disc_addr.trtype];
	if (!ops) {
		up_write(&nvmet_config_sem);
		request_module("nvmet-transport-%d", port->disc_addr.trtype);
		down_write(&nvmet_config_sem);
		ops = nvmet_transports[port->disc_addr.trtype];
		if (!ops) {
			pr_err("transport type %d not supported\n",
				port->disc_addr.trtype);
			return -EINVAL;
		}
	}

	if (!try_module_get(ops->owner))
		return -EINVAL;

	ret = ops->add_port(port);
	if (ret) {
		module_put(ops->owner);
		return ret;
	}

	/* If the transport didn't set inline_data_size, then disable it. */
	if (port->inline_data_size < 0)
		port->inline_data_size = 0;

	port->enabled = true;
	port->tr_ops = ops;
	return 0;
}
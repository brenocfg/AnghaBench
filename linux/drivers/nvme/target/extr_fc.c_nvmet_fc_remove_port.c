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
struct nvmet_port {struct nvmet_fc_port_entry* priv; } ;
struct nvmet_fc_port_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvmet_fc_port_entry*) ; 
 int /*<<< orphan*/  nvmet_fc_portentry_unbind (struct nvmet_fc_port_entry*) ; 

__attribute__((used)) static void
nvmet_fc_remove_port(struct nvmet_port *port)
{
	struct nvmet_fc_port_entry *pe = port->priv;

	nvmet_fc_portentry_unbind(pe);

	kfree(pe);
}
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
struct nvmet_port {struct nvmet_fc_port_entry* priv; } ;
struct nvmet_fc_tgtport {int /*<<< orphan*/  fc_target_port; TYPE_1__* ops; } ;
struct nvmet_fc_port_entry {struct nvmet_fc_tgtport* tgtport; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* discovery_event ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvmet_fc_discovery_chg(struct nvmet_port *port)
{
	struct nvmet_fc_port_entry *pe = port->priv;
	struct nvmet_fc_tgtport *tgtport = pe->tgtport;

	if (tgtport && tgtport->ops->discovery_event)
		tgtport->ops->discovery_event(&tgtport->fc_target_port);
}
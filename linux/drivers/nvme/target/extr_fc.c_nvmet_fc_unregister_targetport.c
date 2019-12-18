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
struct nvmet_fc_tgtport {int dummy; } ;
struct nvmet_fc_target_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nvmet_fc_free_assocs (struct nvmet_fc_tgtport*) ; 
 int /*<<< orphan*/  nvmet_fc_portentry_unbind_tgt (struct nvmet_fc_tgtport*) ; 
 int /*<<< orphan*/  nvmet_fc_tgtport_put (struct nvmet_fc_tgtport*) ; 
 struct nvmet_fc_tgtport* targetport_to_tgtport (struct nvmet_fc_target_port*) ; 

int
nvmet_fc_unregister_targetport(struct nvmet_fc_target_port *target_port)
{
	struct nvmet_fc_tgtport *tgtport = targetport_to_tgtport(target_port);

	nvmet_fc_portentry_unbind_tgt(tgtport);

	/* terminate any outstanding associations */
	__nvmet_fc_free_assocs(tgtport);

	nvmet_fc_tgtport_put(tgtport);

	return 0;
}
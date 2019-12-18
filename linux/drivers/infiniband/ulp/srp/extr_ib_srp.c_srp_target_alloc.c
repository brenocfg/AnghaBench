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
struct srp_target_port {scalar_t__ target_can_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {scalar_t__ can_queue; TYPE_1__ dev; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 struct srp_target_port* host_to_target (struct Scsi_Host*) ; 

__attribute__((used)) static int srp_target_alloc(struct scsi_target *starget)
{
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	struct srp_target_port *target = host_to_target(shost);

	if (target->target_can_queue)
		starget->can_queue = target->target_can_queue;
	return 0;
}
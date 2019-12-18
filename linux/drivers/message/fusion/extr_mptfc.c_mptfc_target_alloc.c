#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_target {TYPE_2__* hostdata; } ;
struct TYPE_5__ {int /*<<< orphan*/  CurrentBus; int /*<<< orphan*/  CurrentTargetID; } ;
struct mptfc_rport_info {struct scsi_target* starget; TYPE_1__ pg0; } ;
struct fc_rport {scalar_t__ dd_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ VirtTarget ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct fc_rport* starget_to_rport (struct scsi_target*) ; 

__attribute__((used)) static int
mptfc_target_alloc(struct scsi_target *starget)
{
	VirtTarget		*vtarget;
	struct fc_rport		*rport;
	struct mptfc_rport_info *ri;
	int			rc;

	vtarget = kzalloc(sizeof(VirtTarget), GFP_KERNEL);
	if (!vtarget)
		return -ENOMEM;
	starget->hostdata = vtarget;

	rc = -ENODEV;
	rport = starget_to_rport(starget);
	if (rport) {
		ri = *((struct mptfc_rport_info **)rport->dd_data);
		if (ri) {	/* better be! */
			vtarget->id = ri->pg0.CurrentTargetID;
			vtarget->channel = ri->pg0.CurrentBus;
			ri->starget = starget;
			rc = 0;
		}
	}
	if (rc != 0) {
		kfree(vtarget);
		starget->hostdata = NULL;
	}

	return rc;
}
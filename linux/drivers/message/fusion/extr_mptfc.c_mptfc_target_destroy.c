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
struct scsi_target {int /*<<< orphan*/ * hostdata; } ;
struct mptfc_rport_info {int /*<<< orphan*/ * starget; } ;
struct fc_rport {scalar_t__ dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct fc_rport* starget_to_rport (struct scsi_target*) ; 

__attribute__((used)) static void
mptfc_target_destroy(struct scsi_target *starget)
{
	struct fc_rport		*rport;
	struct mptfc_rport_info *ri;

	rport = starget_to_rport(starget);
	if (rport) {
		ri = *((struct mptfc_rport_info **)rport->dd_data);
		if (ri)	/* better be! */
			ri->starget = NULL;
	}
	kfree(starget->hostdata);
	starget->hostdata = NULL;
}
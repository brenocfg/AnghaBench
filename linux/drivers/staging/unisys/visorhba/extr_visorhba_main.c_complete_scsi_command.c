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
struct TYPE_2__ {scalar_t__ linuxstat; } ;
struct uiscmdrsp {TYPE_1__ scsi; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;scalar_t__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_scsi_linuxstat (struct uiscmdrsp*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  do_scsi_nolinuxstat (struct uiscmdrsp*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void complete_scsi_command(struct uiscmdrsp *cmdrsp,
				  struct scsi_cmnd *scsicmd)
{
	/* take what we need out of cmdrsp and complete the scsicmd */
	scsicmd->result = cmdrsp->scsi.linuxstat;
	if (cmdrsp->scsi.linuxstat)
		do_scsi_linuxstat(cmdrsp, scsicmd);
	else
		do_scsi_nolinuxstat(cmdrsp, scsicmd);

	scsicmd->scsi_done(scsicmd);
}
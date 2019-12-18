#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct visorhba_devdata {TYPE_3__* dev; int /*<<< orphan*/  idr; } ;
struct TYPE_5__ {int /*<<< orphan*/  result; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
struct uiscmdrsp {scalar_t__ cmdtype; TYPE_2__ scsitaskmgmt; TYPE_1__ scsi; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; int /*<<< orphan*/  visorchannel; } ;

/* Variables and functions */
 scalar_t__ CMD_NOTIFYGUEST_TYPE ; 
 scalar_t__ CMD_SCSITASKMGMT_TYPE ; 
 scalar_t__ CMD_SCSI_TYPE ; 
 int /*<<< orphan*/  IOCHAN_FROM_IOPART ; 
 int /*<<< orphan*/  complete_scsi_command (struct uiscmdrsp*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  complete_taskmgmt_command (int /*<<< orphan*/ *,struct uiscmdrsp*,int /*<<< orphan*/ ) ; 
 struct scsi_cmnd* del_scsipending_ent (struct visorhba_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err_once (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ visorchannel_signalremove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uiscmdrsp*) ; 

__attribute__((used)) static void drain_queue(struct uiscmdrsp *cmdrsp,
			struct visorhba_devdata *devdata)
{
	struct scsi_cmnd *scsicmd;

	while (1) {
		/* queue empty */
		if (visorchannel_signalremove(devdata->dev->visorchannel,
					      IOCHAN_FROM_IOPART,
					      cmdrsp))
			break;
		if (cmdrsp->cmdtype == CMD_SCSI_TYPE) {
			/* scsicmd location is returned by the
			 * deletion
			 */
			scsicmd = del_scsipending_ent(devdata,
						      cmdrsp->scsi.handle);
			if (!scsicmd)
				break;
			/* complete the orig cmd */
			complete_scsi_command(cmdrsp, scsicmd);
		} else if (cmdrsp->cmdtype == CMD_SCSITASKMGMT_TYPE) {
			if (!del_scsipending_ent(devdata,
						 cmdrsp->scsitaskmgmt.handle))
				break;
			complete_taskmgmt_command(&devdata->idr, cmdrsp,
						  cmdrsp->scsitaskmgmt.result);
		} else if (cmdrsp->cmdtype == CMD_NOTIFYGUEST_TYPE)
			dev_err_once(&devdata->dev->device,
				     "ignoring unsupported NOTIFYGUEST\n");
		/* cmdrsp is now available for re-use */
	}
}
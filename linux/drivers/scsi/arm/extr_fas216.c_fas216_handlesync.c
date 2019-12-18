#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct fas216_device {int sync_state; char period; char sof; int /*<<< orphan*/  stp; } ;
struct TYPE_11__ {int /*<<< orphan*/  async_stp; void* phase; int /*<<< orphan*/  msgs; } ;
struct TYPE_10__ {char sync_max_depth; int clockrate; int asyncperiod; } ;
struct TYPE_14__ {TYPE_4__* SCpnt; TYPE_2__ scsi; TYPE_1__ ifcfg; struct fas216_device* device; } ;
struct TYPE_13__ {TYPE_3__* device; } ;
struct TYPE_12__ {size_t id; } ;
typedef  TYPE_5__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SETATN ; 
#define  EXTENDED_MESSAGE 131 
 int /*<<< orphan*/  EXTENDED_SDTR ; 
#define  MESSAGE_REJECT 130 
 void* PHASE_MSGOUT_EXPECT ; 
 int /*<<< orphan*/  fas216_cmd (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_set_sync (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  fas216_syncperiod (TYPE_5__*,char) ; 
 int /*<<< orphan*/  msgqueue_addmsg (int /*<<< orphan*/ *,int,int const,...) ; 
 int /*<<< orphan*/  msgqueue_flush (int /*<<< orphan*/ *) ; 
 int neg_complete ; 
#define  neg_inprogress 129 
#define  neg_invalid 128 
 int neg_targcomplete ; 

__attribute__((used)) static void fas216_handlesync(FAS216_Info *info, char *msg)
{
	struct fas216_device *dev = &info->device[info->SCpnt->device->id];
	enum { sync, async, none, reject } res = none;

#ifdef SCSI2_SYNC
	switch (msg[0]) {
	case MESSAGE_REJECT:
		/* Synchronous transfer request failed.
		 * Note: SCSI II r10:
		 *
		 *  SCSI devices that are capable of synchronous
		 *  data transfers shall not respond to an SDTR
		 *  message with a MESSAGE REJECT message.
		 *
		 * Hence, if we get this condition, we disable
		 * negotiation for this device.
		 */
		if (dev->sync_state == neg_inprogress) {
			dev->sync_state = neg_invalid;
			res = async;
		}
		break;

	case EXTENDED_MESSAGE:
		switch (dev->sync_state) {
		/* We don't accept synchronous transfer requests.
		 * Respond with a MESSAGE_REJECT to prevent a
		 * synchronous transfer agreement from being reached.
		 */
		case neg_invalid:
			res = reject;
			break;

		/* We were not negotiating a synchronous transfer,
		 * but the device sent us a negotiation request.
		 * Honour the request by sending back a SDTR
		 * message containing our capability, limited by
		 * the targets capability.
		 */
		default:
			fas216_cmd(info, CMD_SETATN);
			if (msg[4] > info->ifcfg.sync_max_depth)
				msg[4] = info->ifcfg.sync_max_depth;
			if (msg[3] < 1000 / info->ifcfg.clockrate)
				msg[3] = 1000 / info->ifcfg.clockrate;

			msgqueue_flush(&info->scsi.msgs);
			msgqueue_addmsg(&info->scsi.msgs, 5,
					EXTENDED_MESSAGE, 3, EXTENDED_SDTR,
					msg[3], msg[4]);
			info->scsi.phase = PHASE_MSGOUT_EXPECT;

			/* This is wrong.  The agreement is not in effect
			 * until this message is accepted by the device
			 */
			dev->sync_state = neg_targcomplete;
			res = sync;
			break;

		/* We initiated the synchronous transfer negotiation,
		 * and have successfully received a response from the
		 * target.  The synchronous transfer agreement has been
		 * reached.  Note: if the values returned are out of our
		 * bounds, we must reject the message.
		 */
		case neg_inprogress:
			res = reject;
			if (msg[4] <= info->ifcfg.sync_max_depth &&
			    msg[3] >= 1000 / info->ifcfg.clockrate) {
				dev->sync_state = neg_complete;
				res = sync;
			}
			break;
		}
	}
#else
	res = reject;
#endif

	switch (res) {
	case sync:
		dev->period = msg[3];
		dev->sof    = msg[4];
		dev->stp    = fas216_syncperiod(info, msg[3] * 4);
		fas216_set_sync(info, info->SCpnt->device->id);
		break;

	case reject:
		fas216_cmd(info, CMD_SETATN);
		msgqueue_flush(&info->scsi.msgs);
		msgqueue_addmsg(&info->scsi.msgs, 1, MESSAGE_REJECT);
		info->scsi.phase = PHASE_MSGOUT_EXPECT;
		/* fall through */

	case async:
		dev->period = info->ifcfg.asyncperiod / 4;
		dev->sof    = 0;
		dev->stp    = info->scsi.async_stp;
		fas216_set_sync(info, info->SCpnt->device->id);
		break;

	case none:
		break;
	}
}
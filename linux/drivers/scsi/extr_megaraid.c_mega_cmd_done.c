#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct scsi_cmnd {int result; size_t channel; scalar_t__* cmnd; int* sense_buffer; TYPE_1__* device; } ;
struct scatterlist {int dummy; } ;
struct TYPE_16__ {int state; scalar_t__ raw_mbox; TYPE_6__* epthru; TYPE_5__* pthru; struct scsi_cmnd* cmd; int /*<<< orphan*/  idx; int /*<<< orphan*/  list; } ;
typedef  TYPE_4__ scb_t ;
struct TYPE_17__ {int /*<<< orphan*/  reqsensearea; } ;
typedef  TYPE_5__ mega_passthru ;
struct TYPE_18__ {int /*<<< orphan*/  reqsensearea; } ;
typedef  TYPE_6__ mega_ext_passthru ;
struct TYPE_15__ {int logdrv; int /*<<< orphan*/  cmd; } ;
struct TYPE_19__ {TYPE_3__ m_out; } ;
typedef  TYPE_7__ mbox_t ;
struct TYPE_20__ {int int_status; int* logdrv_chan; int /*<<< orphan*/  completed_list; TYPE_2__* dev; int /*<<< orphan*/ * wr_errors; int /*<<< orphan*/ * rd_errors; TYPE_4__* scb_list; int /*<<< orphan*/  int_waitq; TYPE_4__ int_scb; } ;
typedef  TYPE_8__ adapter_t ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {size_t channel; } ;

/* Variables and functions */
 int ABORTED_COMMAND ; 
 int CHECK_CONDITION ; 
 int CMDID_INT_CMDS ; 
 int DID_ABORT ; 
 int DID_BAD_TARGET ; 
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int DID_OK ; 
 int DID_RESET ; 
 int DRIVER_SENSE ; 
 scalar_t__ INQUIRY ; 
 scalar_t__ IS_RAID_CH (TYPE_8__*,size_t) ; 
 int /*<<< orphan*/  MEGA_MBOXCMD_EXTPTHRU ; 
 int /*<<< orphan*/  MEGA_MBOXCMD_PASSTHRU ; 
 int /*<<< orphan*/  MEGA_MBOXCMD_PASSTHRU64 ; 
 scalar_t__ READ_10 ; 
 scalar_t__ READ_12 ; 
 scalar_t__ READ_6 ; 
 scalar_t__ RELEASE ; 
 int RESERVATION_CONFLICT ; 
 scalar_t__ RESERVE ; 
 int SCB_ABORT ; 
 int SCB_FREE ; 
 int SCB_ISSUED ; 
 int SCB_RESET ; 
 int /*<<< orphan*/  SCSI_LIST (struct scsi_cmnd*) ; 
 scalar_t__ TEST_UNIT_READY ; 
 int TYPE_DISK ; 
 scalar_t__ WRITE_10 ; 
 scalar_t__ WRITE_12 ; 
 scalar_t__ WRITE_6 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,int,int,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mega_free_scb (TYPE_8__*,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 scalar_t__ sg_page (struct scatterlist*) ; 
 scalar_t__ sg_virt (struct scatterlist*) ; 

__attribute__((used)) static void
mega_cmd_done(adapter_t *adapter, u8 completed[], int nstatus, int status)
{
	mega_ext_passthru	*epthru = NULL;
	struct scatterlist	*sgl;
	struct scsi_cmnd	*cmd = NULL;
	mega_passthru	*pthru = NULL;
	mbox_t	*mbox = NULL;
	u8	c;
	scb_t	*scb;
	int	islogical;
	int	cmdid;
	int	i;

	/*
	 * for all the commands completed, call the mid-layer callback routine
	 * and free the scb.
	 */
	for( i = 0; i < nstatus; i++ ) {

		cmdid = completed[i];

		/*
		 * Only free SCBs for the commands coming down from the
		 * mid-layer, not for which were issued internally
		 *
		 * For internal command, restore the status returned by the
		 * firmware so that user can interpret it.
		 */
		if (cmdid == CMDID_INT_CMDS) {
			scb = &adapter->int_scb;

			list_del_init(&scb->list);
			scb->state = SCB_FREE;

			adapter->int_status = status;
			complete(&adapter->int_waitq);
		} else {
			scb = &adapter->scb_list[cmdid];

			/*
			 * Make sure f/w has completed a valid command
			 */
			if( !(scb->state & SCB_ISSUED) || scb->cmd == NULL ) {
				dev_crit(&adapter->dev->dev, "invalid command "
					"Id %d, scb->state:%x, scsi cmd:%p\n",
					cmdid, scb->state, scb->cmd);

				continue;
			}

			/*
			 * Was a abort issued for this command
			 */
			if( scb->state & SCB_ABORT ) {

				dev_warn(&adapter->dev->dev,
					"aborted cmd [%x] complete\n",
					scb->idx);

				scb->cmd->result = (DID_ABORT << 16);

				list_add_tail(SCSI_LIST(scb->cmd),
						&adapter->completed_list);

				mega_free_scb(adapter, scb);

				continue;
			}

			/*
			 * Was a reset issued for this command
			 */
			if( scb->state & SCB_RESET ) {

				dev_warn(&adapter->dev->dev,
					"reset cmd [%x] complete\n",
					scb->idx);

				scb->cmd->result = (DID_RESET << 16);

				list_add_tail(SCSI_LIST(scb->cmd),
						&adapter->completed_list);

				mega_free_scb (adapter, scb);

				continue;
			}

			cmd = scb->cmd;
			pthru = scb->pthru;
			epthru = scb->epthru;
			mbox = (mbox_t *)scb->raw_mbox;

#if MEGA_HAVE_STATS
			{

			int	logdrv = mbox->m_out.logdrv;

			islogical = adapter->logdrv_chan[cmd->channel];
			/*
			 * Maintain an error counter for the logical drive.
			 * Some application like SNMP agent need such
			 * statistics
			 */
			if( status && islogical && (cmd->cmnd[0] == READ_6 ||
						cmd->cmnd[0] == READ_10 ||
						cmd->cmnd[0] == READ_12)) {
				/*
				 * Logical drive number increases by 0x80 when
				 * a logical drive is deleted
				 */
				adapter->rd_errors[logdrv%0x80]++;
			}

			if( status && islogical && (cmd->cmnd[0] == WRITE_6 ||
						cmd->cmnd[0] == WRITE_10 ||
						cmd->cmnd[0] == WRITE_12)) {
				/*
				 * Logical drive number increases by 0x80 when
				 * a logical drive is deleted
				 */
				adapter->wr_errors[logdrv%0x80]++;
			}

			}
#endif
		}

		/*
		 * Do not return the presence of hard disk on the channel so,
		 * inquiry sent, and returned data==hard disk or removable
		 * hard disk and not logical, request should return failure! -
		 * PJ
		 */
		islogical = adapter->logdrv_chan[cmd->device->channel];
		if( cmd->cmnd[0] == INQUIRY && !islogical ) {

			sgl = scsi_sglist(cmd);
			if( sg_page(sgl) ) {
				c = *(unsigned char *) sg_virt(&sgl[0]);
			} else {
				dev_warn(&adapter->dev->dev, "invalid sg\n");
				c = 0;
			}

			if(IS_RAID_CH(adapter, cmd->device->channel) &&
					((c & 0x1F ) == TYPE_DISK)) {
				status = 0xF0;
			}
		}

		/* clear result; otherwise, success returns corrupt value */
		cmd->result = 0;

		/* Convert MegaRAID status to Linux error code */
		switch (status) {
		case 0x00:	/* SUCCESS , i.e. SCSI_STATUS_GOOD */
			cmd->result |= (DID_OK << 16);
			break;

		case 0x02:	/* ERROR_ABORTED, i.e.
				   SCSI_STATUS_CHECK_CONDITION */

			/* set sense_buffer and result fields */
			if( mbox->m_out.cmd == MEGA_MBOXCMD_PASSTHRU ||
				mbox->m_out.cmd == MEGA_MBOXCMD_PASSTHRU64 ) {

				memcpy(cmd->sense_buffer, pthru->reqsensearea,
						14);

				cmd->result = (DRIVER_SENSE << 24) |
					(DID_OK << 16) |
					(CHECK_CONDITION << 1);
			}
			else {
				if (mbox->m_out.cmd == MEGA_MBOXCMD_EXTPTHRU) {

					memcpy(cmd->sense_buffer,
						epthru->reqsensearea, 14);

					cmd->result = (DRIVER_SENSE << 24) |
						(DID_OK << 16) |
						(CHECK_CONDITION << 1);
				} else {
					cmd->sense_buffer[0] = 0x70;
					cmd->sense_buffer[2] = ABORTED_COMMAND;
					cmd->result |= (CHECK_CONDITION << 1);
				}
			}
			break;

		case 0x08:	/* ERR_DEST_DRIVE_FAILED, i.e.
				   SCSI_STATUS_BUSY */
			cmd->result |= (DID_BUS_BUSY << 16) | status;
			break;

		default:
#if MEGA_HAVE_CLUSTERING
			/*
			 * If TEST_UNIT_READY fails, we know
			 * MEGA_RESERVATION_STATUS failed
			 */
			if( cmd->cmnd[0] == TEST_UNIT_READY ) {
				cmd->result |= (DID_ERROR << 16) |
					(RESERVATION_CONFLICT << 1);
			}
			else
			/*
			 * Error code returned is 1 if Reserve or Release
			 * failed or the input parameter is invalid
			 */
			if( status == 1 &&
				(cmd->cmnd[0] == RESERVE ||
					 cmd->cmnd[0] == RELEASE) ) {

				cmd->result |= (DID_ERROR << 16) |
					(RESERVATION_CONFLICT << 1);
			}
			else
#endif
				cmd->result |= (DID_BAD_TARGET << 16)|status;
		}

		mega_free_scb(adapter, scb);

		/* Add Scsi_Command to end of completed queue */
		list_add_tail(SCSI_LIST(cmd), &adapter->completed_list);
	}
}
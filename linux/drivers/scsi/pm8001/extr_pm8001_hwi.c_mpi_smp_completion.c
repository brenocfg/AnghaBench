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
typedef  size_t u32 ;
struct task_status_struct {void* stat; void* resp; void* open_rej_reason; int /*<<< orphan*/  residual; } ;
struct smp_completion_resp {int /*<<< orphan*/  tag; int /*<<< orphan*/  status; } ;
struct sas_task {int task_state_flags; int /*<<< orphan*/  (* task_done ) (struct sas_task*) ;int /*<<< orphan*/  task_state_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  lldd_task; struct task_status_struct task_status; } ;
struct pm8001_hba_info {struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_device {int /*<<< orphan*/  running_req; } ;
struct pm8001_ccb_info {struct pm8001_device* device; struct sas_task* task; } ;

/* Variables and functions */
#define  IO_ABORTED 148 
#define  IO_DS_IN_RECOVERY 147 
#define  IO_DS_NON_OPERATIONAL 146 
#define  IO_ERROR_HW_TIMEOUT 145 
#define  IO_ERROR_INTERNAL_SMP_RESOURCE 144 
#define  IO_NO_DEVICE 143 
#define  IO_OPEN_CNX_ERROR_BAD_DESTINATION 142 
#define  IO_OPEN_CNX_ERROR_BREAK 141 
#define  IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED 140 
#define  IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY 139 
#define  IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS 138 
#define  IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED 137 
#define  IO_OPEN_CNX_ERROR_WRONG_DESTINATION 136 
#define  IO_OPEN_CNX_ERROR_ZONE_VIOLATION 135 
#define  IO_OVERFLOW 134 
#define  IO_PORT_IN_RESET 133 
#define  IO_SUCCESS 132 
#define  IO_XFER_ERROR_BREAK 131 
#define  IO_XFER_ERROR_PHY_NOT_READY 130 
#define  IO_XFER_ERROR_RX_FRAME 129 
#define  IO_XFER_OPEN_RETRY_TIMEOUT 128 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_IO_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 void* SAM_STAT_BUSY ; 
 void* SAM_STAT_GOOD ; 
 void* SAS_ABORTED_TASK ; 
 void* SAS_DATA_OVERRUN ; 
 void* SAS_DEV_NO_RESPONSE ; 
 void* SAS_OPEN_REJECT ; 
 void* SAS_OREJ_BAD_DEST ; 
 void* SAS_OREJ_CONN_RATE ; 
 void* SAS_OREJ_RSVD_CONT0 ; 
 void* SAS_OREJ_RSVD_RETRY ; 
 void* SAS_OREJ_UNKNOWN ; 
 void* SAS_OREJ_WRONG_DEST ; 
 void* SAS_PHY_DOWN ; 
 void* SAS_QUEUE_FULL ; 
 int SAS_TASK_AT_INITIATOR ; 
 void* SAS_TASK_COMPLETE ; 
 int SAS_TASK_STATE_ABORTED ; 
 int SAS_TASK_STATE_DONE ; 
 int SAS_TASK_STATE_PENDING ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pm8001_ccb_task_free (struct pm8001_hba_info*,struct sas_task*,struct pm8001_ccb_info*,size_t) ; 
 int /*<<< orphan*/  pm8001_handle_event (struct pm8001_hba_info*,struct pm8001_device*,int const) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sas_task*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
mpi_smp_completion(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	struct sas_task *t;
	struct pm8001_ccb_info *ccb;
	unsigned long flags;
	u32 status;
	u32 tag;
	struct smp_completion_resp *psmpPayload;
	struct task_status_struct *ts;
	struct pm8001_device *pm8001_dev;

	psmpPayload = (struct smp_completion_resp *)(piomb + 4);
	status = le32_to_cpu(psmpPayload->status);
	tag = le32_to_cpu(psmpPayload->tag);

	ccb = &pm8001_ha->ccb_info[tag];
	t = ccb->task;
	ts = &t->task_status;
	pm8001_dev = ccb->device;
	if (status)
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("smp IO status 0x%x\n", status));
	if (unlikely(!t || !t->lldd_task || !t->dev))
		return;

	switch (status) {
	case IO_SUCCESS:
		PM8001_IO_DBG(pm8001_ha, pm8001_printk("IO_SUCCESS\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_GOOD;
		if (pm8001_dev)
			pm8001_dev->running_req--;
		break;
	case IO_ABORTED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_ABORTED IOMB\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		if (pm8001_dev)
			pm8001_dev->running_req--;
		break;
	case IO_OVERFLOW:
		PM8001_IO_DBG(pm8001_ha, pm8001_printk("IO_UNDERFLOW\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		ts->residual = 0;
		if (pm8001_dev)
			pm8001_dev->running_req--;
		break;
	case IO_NO_DEVICE:
		PM8001_IO_DBG(pm8001_ha, pm8001_printk("IO_NO_DEVICE\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_PHY_DOWN;
		break;
	case IO_ERROR_HW_TIMEOUT:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_ERROR_HW_TIMEOUT\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_BUSY;
		break;
	case IO_XFER_ERROR_BREAK:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_BREAK\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_BUSY;
		break;
	case IO_XFER_ERROR_PHY_NOT_READY:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_PHY_NOT_READY\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_BUSY;
		break;
	case IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		PM8001_IO_DBG(pm8001_ha,
		pm8001_printk("IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_UNKNOWN;
		break;
	case IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_UNKNOWN;
		break;
	case IO_OPEN_CNX_ERROR_BREAK:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_BREAK\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_CONT0;
		break;
	case IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_UNKNOWN;
		pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
		break;
	case IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_BAD_DESTINATION\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_BAD_DEST;
		break;
	case IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_CONNECTION_RATE_"
			"NOT_SUPPORTED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_CONN_RATE;
		break;
	case IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		PM8001_IO_DBG(pm8001_ha,
		       pm8001_printk("IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_WRONG_DEST;
		break;
	case IO_XFER_ERROR_RX_FRAME:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_RX_FRAME\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		break;
	case IO_XFER_OPEN_RETRY_TIMEOUT:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_OPEN_RETRY_TIMEOUT\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_RETRY;
		break;
	case IO_ERROR_INTERNAL_SMP_RESOURCE:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_ERROR_INTERNAL_SMP_RESOURCE\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_QUEUE_FULL;
		break;
	case IO_PORT_IN_RESET:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_PORT_IN_RESET\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_RETRY;
		break;
	case IO_DS_NON_OPERATIONAL:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_DS_NON_OPERATIONAL\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		break;
	case IO_DS_IN_RECOVERY:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_DS_IN_RECOVERY\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_RETRY;
		break;
	case IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_RETRY;
		break;
	default:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("Unknown status 0x%x\n", status));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		/* not allowed case. Therefore, return failed status */
		break;
	}
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	if (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) {
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		PM8001_FAIL_DBG(pm8001_ha, pm8001_printk("task 0x%p done with"
			" io_status 0x%x resp 0x%x "
			"stat 0x%x but aborted by upper layer!\n",
			t, status, ts->resp, ts->stat));
		pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
	} else {
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
		mb();/* in order to force CPU ordering */
		t->task_done(t);
	}
}
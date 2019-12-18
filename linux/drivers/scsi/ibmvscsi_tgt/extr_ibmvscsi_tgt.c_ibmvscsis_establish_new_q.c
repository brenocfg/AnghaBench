#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
struct TYPE_4__ {scalar_t__ timer_pops; } ;
struct TYPE_3__ {int /*<<< orphan*/  unit_id; } ;
struct scsi_info {int /*<<< orphan*/  state; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_dev; scalar_t__ credit; scalar_t__ debit; TYPE_2__ rsp_q_timer; int /*<<< orphan*/  flags; TYPE_1__ dds; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
#define  H_CLOSED 132 
#define  H_DROPPED 131 
 int /*<<< orphan*/  H_ENABLE_PREPARE_FOR_SUSPEND ; 
#define  H_HARDWARE 130 
 long H_NOT_FOUND ; 
#define  H_PARAMETER 129 
#define  H_SUCCESS 128 
 scalar_t__ INIT_MSG ; 
 int /*<<< orphan*/  PREP_FOR_SUSPEND_ENABLED ; 
 int /*<<< orphan*/  PRESERVE_FLAG_FIELDS ; 
 int /*<<< orphan*/  UNDEFINED ; 
 scalar_t__ UNUSED_FORMAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,long) ; 
 long h_vioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ibmvscsis_check_init_msg (struct scsi_info*,scalar_t__*) ; 
 long ibmvscsis_handle_init_msg (struct scsi_info*) ; 
 long ibmvscsis_send_init_message (struct scsi_info*,scalar_t__) ; 
 long vio_enable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ibmvscsis_establish_new_q(struct scsi_info *vscsi)
{
	long rc = ADAPT_SUCCESS;
	uint format;

	rc = h_vioctl(vscsi->dds.unit_id, H_ENABLE_PREPARE_FOR_SUSPEND, 30000,
		      0, 0, 0, 0);
	if (rc == H_SUCCESS)
		vscsi->flags |= PREP_FOR_SUSPEND_ENABLED;
	else if (rc != H_NOT_FOUND)
		dev_err(&vscsi->dev, "Error from Enable Prepare for Suspend: %ld\n",
			rc);

	vscsi->flags &= PRESERVE_FLAG_FIELDS;
	vscsi->rsp_q_timer.timer_pops = 0;
	vscsi->debit = 0;
	vscsi->credit = 0;

	rc = vio_enable_interrupts(vscsi->dma_dev);
	if (rc) {
		dev_warn(&vscsi->dev, "establish_new_q: failed to enable interrupts, rc %ld\n",
			 rc);
		return rc;
	}

	rc = ibmvscsis_check_init_msg(vscsi, &format);
	if (rc) {
		dev_err(&vscsi->dev, "establish_new_q: check_init_msg failed, rc %ld\n",
			rc);
		return rc;
	}

	if (format == UNUSED_FORMAT) {
		rc = ibmvscsis_send_init_message(vscsi, INIT_MSG);
		switch (rc) {
		case H_SUCCESS:
		case H_DROPPED:
		case H_CLOSED:
			rc = ADAPT_SUCCESS;
			break;

		case H_PARAMETER:
		case H_HARDWARE:
			break;

		default:
			vscsi->state = UNDEFINED;
			rc = H_HARDWARE;
			break;
		}
	} else if (format == INIT_MSG) {
		rc = ibmvscsis_handle_init_msg(vscsi);
	}

	return rc;
}
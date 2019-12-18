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
struct xcopy_op {int /*<<< orphan*/  xop_work; struct se_cmd* xop_se_cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  emulate_3pc; } ;
struct se_device {TYPE_1__ dev_attrib; } ;
struct se_cmd {int* t_task_cdb; scalar_t__ data_length; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  TCM_NO_SENSE ; 
 int /*<<< orphan*/  TCM_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  TCM_PARAMETER_LIST_LENGTH_ERROR ; 
 int /*<<< orphan*/  TCM_UNSUPPORTED_SCSI_OPCODE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ XCOPY_HDR_LEN ; 
 int /*<<< orphan*/  kfree (struct xcopy_op*) ; 
 struct xcopy_op* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_xcopy_do_work ; 
 int /*<<< orphan*/  xcopy_wq ; 

sense_reason_t target_do_xcopy(struct se_cmd *se_cmd)
{
	struct se_device *dev = se_cmd->se_dev;
	struct xcopy_op *xop;
	unsigned int sa;

	if (!dev->dev_attrib.emulate_3pc) {
		pr_err("EXTENDED_COPY operation explicitly disabled\n");
		return TCM_UNSUPPORTED_SCSI_OPCODE;
	}

	sa = se_cmd->t_task_cdb[1] & 0x1f;
	if (sa != 0x00) {
		pr_err("EXTENDED_COPY(LID4) not supported\n");
		return TCM_UNSUPPORTED_SCSI_OPCODE;
	}

	if (se_cmd->data_length == 0) {
		target_complete_cmd(se_cmd, SAM_STAT_GOOD);
		return TCM_NO_SENSE;
	}
	if (se_cmd->data_length < XCOPY_HDR_LEN) {
		pr_err("XCOPY parameter truncation: length %u < hdr_len %u\n",
				se_cmd->data_length, XCOPY_HDR_LEN);
		return TCM_PARAMETER_LIST_LENGTH_ERROR;
	}

	xop = kzalloc(sizeof(struct xcopy_op), GFP_KERNEL);
	if (!xop)
		goto err;
	xop->xop_se_cmd = se_cmd;
	INIT_WORK(&xop->xop_work, target_xcopy_do_work);
	if (WARN_ON_ONCE(!queue_work(xcopy_wq, &xop->xop_work)))
		goto free;
	return TCM_NO_SENSE;

free:
	kfree(xop);

err:
	return TCM_OUT_OF_RESOURCES;
}
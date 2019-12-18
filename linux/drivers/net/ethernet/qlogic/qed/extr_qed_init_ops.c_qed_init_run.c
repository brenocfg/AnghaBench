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
struct TYPE_6__ {int /*<<< orphan*/  delay; } ;
struct TYPE_5__ {int /*<<< orphan*/  op_data; } ;
union init_op {int /*<<< orphan*/  callback; TYPE_3__ delay; int /*<<< orphan*/  if_phase; int /*<<< orphan*/  if_mode; int /*<<< orphan*/  read; int /*<<< orphan*/  write; TYPE_2__ raw; } ;
typedef  size_t u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/ * unzip_buf; struct qed_dev* cdev; } ;
struct qed_dev {TYPE_1__* fw_data; } ;
struct TYPE_4__ {size_t init_ops_size; union init_op* init_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GET_FIELD (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_CALLBACK_OP_OP ; 
 int /*<<< orphan*/  INIT_IF_PHASE_OP_DMAE_ENABLE ; 
#define  INIT_OP_CALLBACK 133 
#define  INIT_OP_DELAY 132 
#define  INIT_OP_IF_MODE 131 
#define  INIT_OP_IF_PHASE 130 
#define  INIT_OP_READ 129 
#define  INIT_OP_WRITE 128 
 int MAX_ZIPPED_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int qed_init_cmd_cb (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *) ; 
 size_t qed_init_cmd_mode (struct qed_hwfn*,int /*<<< orphan*/ *,int) ; 
 size_t qed_init_cmd_phase (struct qed_hwfn*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  qed_init_cmd_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *) ; 
 int qed_init_cmd_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (size_t) ; 

int qed_init_run(struct qed_hwfn *p_hwfn,
		 struct qed_ptt *p_ptt, int phase, int phase_id, int modes)
{
	struct qed_dev *cdev = p_hwfn->cdev;
	u32 cmd_num, num_init_ops;
	union init_op *init_ops;
	bool b_dmae = false;
	int rc = 0;

	num_init_ops = cdev->fw_data->init_ops_size;
	init_ops = cdev->fw_data->init_ops;

	p_hwfn->unzip_buf = kzalloc(MAX_ZIPPED_SIZE * 4, GFP_ATOMIC);
	if (!p_hwfn->unzip_buf)
		return -ENOMEM;

	for (cmd_num = 0; cmd_num < num_init_ops; cmd_num++) {
		union init_op *cmd = &init_ops[cmd_num];
		u32 data = le32_to_cpu(cmd->raw.op_data);

		switch (GET_FIELD(data, INIT_CALLBACK_OP_OP)) {
		case INIT_OP_WRITE:
			rc = qed_init_cmd_wr(p_hwfn, p_ptt, &cmd->write,
					     b_dmae);
			break;
		case INIT_OP_READ:
			qed_init_cmd_rd(p_hwfn, p_ptt, &cmd->read);
			break;
		case INIT_OP_IF_MODE:
			cmd_num += qed_init_cmd_mode(p_hwfn, &cmd->if_mode,
						     modes);
			break;
		case INIT_OP_IF_PHASE:
			cmd_num += qed_init_cmd_phase(p_hwfn, &cmd->if_phase,
						      phase, phase_id);
			b_dmae = GET_FIELD(data, INIT_IF_PHASE_OP_DMAE_ENABLE);
			break;
		case INIT_OP_DELAY:
			/* qed_init_run is always invoked from
			 * sleep-able context
			 */
			udelay(le32_to_cpu(cmd->delay.delay));
			break;

		case INIT_OP_CALLBACK:
			rc = qed_init_cmd_cb(p_hwfn, p_ptt, &cmd->callback);
			break;
		}

		if (rc)
			break;
	}

	kfree(p_hwfn->unzip_buf);
	p_hwfn->unzip_buf = NULL;
	return rc;
}
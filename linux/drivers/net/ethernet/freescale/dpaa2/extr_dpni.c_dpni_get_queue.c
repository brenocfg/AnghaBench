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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpni_rsp_get_queue {int /*<<< orphan*/  qdbin; int /*<<< orphan*/  fqid; int /*<<< orphan*/  user_context; int /*<<< orphan*/  flc; int /*<<< orphan*/  flags; int /*<<< orphan*/  dest_prio; int /*<<< orphan*/  dest_id; } ;
struct dpni_queue_id {int /*<<< orphan*/  qdbin; void* fqid; } ;
struct TYPE_4__ {void* value; void* stash_control; } ;
struct TYPE_3__ {void* hold_active; void* type; int /*<<< orphan*/  priority; void* id; } ;
struct dpni_queue {void* user_context; TYPE_2__ flc; TYPE_1__ destination; } ;
struct dpni_cmd_get_queue {int qtype; void* index; void* tc; } ;
typedef  enum dpni_queue_type { ____Placeholder_dpni_queue_type } dpni_queue_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEST_TYPE ; 
 int /*<<< orphan*/  DPNI_CMDID_GET_QUEUE ; 
 int /*<<< orphan*/  HOLD_ACTIVE ; 
 int /*<<< orphan*/  STASH_CTRL ; 
 void* dpni_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_get_queue(struct fsl_mc_io *mc_io,
		   u32 cmd_flags,
		   u16 token,
		   enum dpni_queue_type qtype,
		   u8 tc,
		   u8 index,
		   struct dpni_queue *queue,
		   struct dpni_queue_id *qid)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_get_queue *cmd_params;
	struct dpni_rsp_get_queue *rsp_params;
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_GET_QUEUE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpni_cmd_get_queue *)cmd.params;
	cmd_params->qtype = qtype;
	cmd_params->tc = tc;
	cmd_params->index = index;

	/* send command to mc */
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpni_rsp_get_queue *)cmd.params;
	queue->destination.id = le32_to_cpu(rsp_params->dest_id);
	queue->destination.priority = rsp_params->dest_prio;
	queue->destination.type = dpni_get_field(rsp_params->flags,
						 DEST_TYPE);
	queue->flc.stash_control = dpni_get_field(rsp_params->flags,
						  STASH_CTRL);
	queue->destination.hold_active = dpni_get_field(rsp_params->flags,
							HOLD_ACTIVE);
	queue->flc.value = le64_to_cpu(rsp_params->flc);
	queue->user_context = le64_to_cpu(rsp_params->user_context);
	qid->fqid = le32_to_cpu(rsp_params->fqid);
	qid->qdbin = le16_to_cpu(rsp_params->qdbin);

	return 0;
}
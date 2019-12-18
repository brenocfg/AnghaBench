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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  task_abort ;
struct task_abort_req {void* tag; void* device_id; void* abort_all; void* tag_to_abort; } ;
struct pm8001_hba_info {struct inbound_queue_table* inbnd_q_tbl; } ;
struct inbound_queue_table {int dummy; } ;

/* Variables and functions */
 int ABORT_ALL ; 
 int ABORT_MASK ; 
 int ABORT_SINGLE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct task_abort_req*,int /*<<< orphan*/ ,int) ; 
 int pm8001_mpi_build_cmd (struct pm8001_hba_info*,struct inbound_queue_table*,int,struct task_abort_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_task_abort(struct pm8001_hba_info *pm8001_ha, u32 opc,
	u32 dev_id, u8 flag, u32 task_tag, u32 cmd_tag)
{
	struct task_abort_req task_abort;
	struct inbound_queue_table *circularQ;
	int ret;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	memset(&task_abort, 0, sizeof(task_abort));
	if (ABORT_SINGLE == (flag & ABORT_MASK)) {
		task_abort.abort_all = 0;
		task_abort.device_id = cpu_to_le32(dev_id);
		task_abort.tag_to_abort = cpu_to_le32(task_tag);
		task_abort.tag = cpu_to_le32(cmd_tag);
	} else if (ABORT_ALL == (flag & ABORT_MASK)) {
		task_abort.abort_all = cpu_to_le32(1);
		task_abort.device_id = cpu_to_le32(dev_id);
		task_abort.tag = cpu_to_le32(cmd_tag);
	}
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &task_abort, 0);
	return ret;
}
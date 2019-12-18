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
typedef  int /*<<< orphan*/  u64 ;
struct scsi_cmnd {TYPE_3__* device; } ;
struct fib {int hbacmd_size; scalar_t__ hw_sgl_pa; } ;
struct aac_hba_sgl {int dummy; } ;
struct aac_hba_cmd_req {int /*<<< orphan*/  emb_data_desc_count; } ;
struct aac_dev {TYPE_1__* scsi_host_ptr; } ;
typedef  int /*<<< orphan*/  fib_callback ;
struct TYPE_6__ {TYPE_2__* host; } ;
struct TYPE_5__ {scalar_t__ hostdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  sg_tablesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBA_IU_TYPE_SCSI_CMD_REQ ; 
 long aac_build_sghba (struct scsi_cmnd*,struct aac_hba_cmd_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aac_hba_cmd_req* aac_construct_hbacmd (struct fib*,struct scsi_cmnd*) ; 
 scalar_t__ aac_hba_callback ; 
 int aac_hba_send (int /*<<< orphan*/ ,struct fib*,int /*<<< orphan*/ ,void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aac_adapter_hba(struct fib *fib, struct scsi_cmnd *cmd)
{
	struct aac_hba_cmd_req *hbacmd = aac_construct_hbacmd(fib, cmd);
	struct aac_dev *dev;
	long ret;

	dev = (struct aac_dev *)cmd->device->host->hostdata;

	ret = aac_build_sghba(cmd, hbacmd,
		dev->scsi_host_ptr->sg_tablesize, (u64)fib->hw_sgl_pa);
	if (ret < 0)
		return ret;

	/*
	 *	Now send the HBA command to the adapter
	 */
	fib->hbacmd_size = 64 + le32_to_cpu(hbacmd->emb_data_desc_count) *
		sizeof(struct aac_hba_sgl);

	return aac_hba_send(HBA_IU_TYPE_SCSI_CMD_REQ, fib,
				  (fib_callback) aac_hba_callback,
				  (void *) cmd);
}
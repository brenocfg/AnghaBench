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
struct TYPE_4__ {scalar_t__ addr; } ;
struct iser_mem_reg {TYPE_2__ sge; int /*<<< orphan*/  rkey; } ;
struct iser_data_buf {int dummy; } ;
struct iser_ctrl {int /*<<< orphan*/  read_va; int /*<<< orphan*/  read_stag; int /*<<< orphan*/  flags; } ;
struct iscsi_task {int /*<<< orphan*/  itt; struct iscsi_iser_task* dd_data; } ;
struct TYPE_3__ {struct iser_ctrl iser_header; } ;
struct iscsi_iser_task {struct iser_mem_reg* rdma_reg; struct iser_data_buf* prot; int /*<<< orphan*/  sc; struct iser_data_buf* data; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 size_t ISER_DIR_IN ; 
 int /*<<< orphan*/  ISER_RSV ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int iser_dma_map_task_data (struct iscsi_iser_task*,struct iser_data_buf*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_err (char*) ; 
 int iser_reg_rdma_mem (struct iscsi_iser_task*,size_t,int) ; 
 scalar_t__ scsi_prot_sg_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iser_prepare_read_cmd(struct iscsi_task *task)

{
	struct iscsi_iser_task *iser_task = task->dd_data;
	struct iser_mem_reg *mem_reg;
	int err;
	struct iser_ctrl *hdr = &iser_task->desc.iser_header;
	struct iser_data_buf *buf_in = &iser_task->data[ISER_DIR_IN];

	err = iser_dma_map_task_data(iser_task,
				     buf_in,
				     ISER_DIR_IN,
				     DMA_FROM_DEVICE);
	if (err)
		return err;

	if (scsi_prot_sg_count(iser_task->sc)) {
		struct iser_data_buf *pbuf_in = &iser_task->prot[ISER_DIR_IN];

		err = iser_dma_map_task_data(iser_task,
					     pbuf_in,
					     ISER_DIR_IN,
					     DMA_FROM_DEVICE);
		if (err)
			return err;
	}

	err = iser_reg_rdma_mem(iser_task, ISER_DIR_IN, false);
	if (err) {
		iser_err("Failed to set up Data-IN RDMA\n");
		return err;
	}
	mem_reg = &iser_task->rdma_reg[ISER_DIR_IN];

	hdr->flags    |= ISER_RSV;
	hdr->read_stag = cpu_to_be32(mem_reg->rkey);
	hdr->read_va   = cpu_to_be64(mem_reg->sge.addr);

	iser_dbg("Cmd itt:%d READ tags RKEY:%#.4X VA:%#llX\n",
		 task->itt, mem_reg->rkey,
		 (unsigned long long)mem_reg->sge.addr);

	return 0;
}
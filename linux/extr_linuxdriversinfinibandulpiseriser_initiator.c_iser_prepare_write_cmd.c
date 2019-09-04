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
struct TYPE_3__ {int /*<<< orphan*/  lkey; scalar_t__ addr; } ;
struct iser_mem_reg {TYPE_1__ sge; int /*<<< orphan*/  rkey; } ;
struct iser_data_buf {unsigned int data_len; } ;
struct iser_ctrl {int /*<<< orphan*/  write_va; int /*<<< orphan*/  write_stag; int /*<<< orphan*/  flags; } ;
struct iscsi_task {int /*<<< orphan*/  itt; struct iscsi_iser_task* dd_data; } ;
struct TYPE_4__ {int num_sge; struct ib_sge* tx_sg; struct iser_ctrl iser_header; } ;
struct iscsi_iser_task {TYPE_2__ desc; struct iser_mem_reg* rdma_reg; struct iser_data_buf* prot; int /*<<< orphan*/  sc; struct iser_data_buf* data; } ;
struct ib_sge {unsigned int length; int /*<<< orphan*/  lkey; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 size_t ISER_DIR_OUT ; 
 int /*<<< orphan*/  ISER_WSV ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ ,unsigned int,...) ; 
 int iser_dma_map_task_data (struct iscsi_iser_task*,struct iser_data_buf*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_err (char*) ; 
 int iser_reg_rdma_mem (struct iscsi_iser_task*,size_t,int) ; 
 scalar_t__ scsi_prot_sg_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iser_prepare_write_cmd(struct iscsi_task *task,
		       unsigned int imm_sz,
		       unsigned int unsol_sz,
		       unsigned int edtl)
{
	struct iscsi_iser_task *iser_task = task->dd_data;
	struct iser_mem_reg *mem_reg;
	int err;
	struct iser_ctrl *hdr = &iser_task->desc.iser_header;
	struct iser_data_buf *buf_out = &iser_task->data[ISER_DIR_OUT];
	struct ib_sge *tx_dsg = &iser_task->desc.tx_sg[1];

	err = iser_dma_map_task_data(iser_task,
				     buf_out,
				     ISER_DIR_OUT,
				     DMA_TO_DEVICE);
	if (err)
		return err;

	if (scsi_prot_sg_count(iser_task->sc)) {
		struct iser_data_buf *pbuf_out = &iser_task->prot[ISER_DIR_OUT];

		err = iser_dma_map_task_data(iser_task,
					     pbuf_out,
					     ISER_DIR_OUT,
					     DMA_TO_DEVICE);
		if (err)
			return err;
	}

	err = iser_reg_rdma_mem(iser_task, ISER_DIR_OUT,
				buf_out->data_len == imm_sz);
	if (err != 0) {
		iser_err("Failed to register write cmd RDMA mem\n");
		return err;
	}

	mem_reg = &iser_task->rdma_reg[ISER_DIR_OUT];

	if (unsol_sz < edtl) {
		hdr->flags     |= ISER_WSV;
		if (buf_out->data_len > imm_sz) {
			hdr->write_stag = cpu_to_be32(mem_reg->rkey);
			hdr->write_va = cpu_to_be64(mem_reg->sge.addr + unsol_sz);
		}

		iser_dbg("Cmd itt:%d, WRITE tags, RKEY:%#.4X VA:%#llX + unsol:%d\n",
			 task->itt, mem_reg->rkey,
			 (unsigned long long)mem_reg->sge.addr, unsol_sz);
	}

	if (imm_sz > 0) {
		iser_dbg("Cmd itt:%d, WRITE, adding imm.data sz: %d\n",
			 task->itt, imm_sz);
		tx_dsg->addr = mem_reg->sge.addr;
		tx_dsg->length = imm_sz;
		tx_dsg->lkey = mem_reg->sge.lkey;
		iser_task->desc.num_sge = 2;
	}

	return 0;
}
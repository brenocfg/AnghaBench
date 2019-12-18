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
struct iser_mem_reg {struct iser_fr_desc* mem_h; } ;
struct iser_fr_desc {int sig_protected; int /*<<< orphan*/  rsc; } ;
struct iser_device {TYPE_2__* reg_ops; } ;
struct iser_data_buf {int dma_nents; } ;
struct iscsi_iser_task {int /*<<< orphan*/ * prot; int /*<<< orphan*/  sc; struct iser_mem_reg* rdma_reg; struct iser_data_buf* data; TYPE_1__* iser_conn; } ;
struct ib_conn {struct iser_device* device; } ;
typedef  enum iser_data_dir { ____Placeholder_iser_data_dir } iser_data_dir ;
struct TYPE_4__ {int /*<<< orphan*/  (* reg_desc_put ) (struct ib_conn*,struct iser_fr_desc*) ;struct iser_fr_desc* (* reg_desc_get ) (struct ib_conn*) ;} ;
struct TYPE_3__ {struct ib_conn ib_conn; } ;

/* Variables and functions */
 scalar_t__ SCSI_PROT_NORMAL ; 
 int /*<<< orphan*/  iser_always_reg ; 
 int iser_reg_data_sg (struct iscsi_iser_task*,struct iser_data_buf*,struct iser_fr_desc*,int,struct iser_mem_reg*) ; 
 int iser_reg_sig_mr (struct iscsi_iser_task*,struct iser_data_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct iser_mem_reg*) ; 
 scalar_t__ scsi_get_prot_op (int /*<<< orphan*/ ) ; 
 struct iser_fr_desc* stub1 (struct ib_conn*) ; 
 int /*<<< orphan*/  stub2 (struct ib_conn*,struct iser_fr_desc*) ; 
 scalar_t__ unlikely (int) ; 

int iser_reg_rdma_mem(struct iscsi_iser_task *task,
		      enum iser_data_dir dir,
		      bool all_imm)
{
	struct ib_conn *ib_conn = &task->iser_conn->ib_conn;
	struct iser_device *device = ib_conn->device;
	struct iser_data_buf *mem = &task->data[dir];
	struct iser_mem_reg *reg = &task->rdma_reg[dir];
	struct iser_fr_desc *desc = NULL;
	bool use_dma_key;
	int err;

	use_dma_key = mem->dma_nents == 1 && (all_imm || !iser_always_reg) &&
		      scsi_get_prot_op(task->sc) == SCSI_PROT_NORMAL;

	if (!use_dma_key) {
		desc = device->reg_ops->reg_desc_get(ib_conn);
		reg->mem_h = desc;
	}

	if (scsi_get_prot_op(task->sc) == SCSI_PROT_NORMAL) {
		err = iser_reg_data_sg(task, mem, desc, use_dma_key, reg);
		if (unlikely(err))
			goto err_reg;
	} else {
		err = iser_reg_sig_mr(task, mem, &task->prot[dir],
				      &desc->rsc, reg);
		if (unlikely(err))
			goto err_reg;

		desc->sig_protected = 1;
	}

	return 0;

err_reg:
	if (desc)
		device->reg_ops->reg_desc_put(ib_conn, desc);

	return err;
}
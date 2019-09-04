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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct se_cmd {int /*<<< orphan*/  t_data_nents; int /*<<< orphan*/  t_data_sg; int /*<<< orphan*/  t_prot_nents; int /*<<< orphan*/  t_prot_sg; } ;
struct isert_conn {int /*<<< orphan*/  qp; TYPE_1__* cm_id; } ;
struct isert_cmd {int ctx_init_done; int /*<<< orphan*/  rw; scalar_t__ read_stag; int /*<<< orphan*/  read_va; TYPE_2__* iscsi_cmd; scalar_t__ write_stag; int /*<<< orphan*/  write_va; } ;
struct ib_sig_attrs {int dummy; } ;
struct ib_send_wr {int dummy; } ;
struct ib_cqe {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {scalar_t__ write_data_done; struct se_cmd se_cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (scalar_t__) ; 
 int /*<<< orphan*/  isert_err (char*,struct isert_cmd*) ; 
 scalar_t__ isert_prot_cmd (struct isert_conn*,struct se_cmd*) ; 
 int isert_set_sig_attrs (struct se_cmd*,struct ib_sig_attrs*) ; 
 int rdma_rw_ctx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int rdma_rw_ctx_post (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_cqe*,struct ib_send_wr*) ; 
 int rdma_rw_ctx_signature_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_sig_attrs*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int target_reverse_dma_direction (struct se_cmd*) ; 

__attribute__((used)) static int
isert_rdma_rw_ctx_post(struct isert_cmd *cmd, struct isert_conn *conn,
		struct ib_cqe *cqe, struct ib_send_wr *chain_wr)
{
	struct se_cmd *se_cmd = &cmd->iscsi_cmd->se_cmd;
	enum dma_data_direction dir = target_reverse_dma_direction(se_cmd);
	u8 port_num = conn->cm_id->port_num;
	u64 addr;
	u32 rkey, offset;
	int ret;

	if (cmd->ctx_init_done)
		goto rdma_ctx_post;

	if (dir == DMA_FROM_DEVICE) {
		addr = cmd->write_va;
		rkey = cmd->write_stag;
		offset = cmd->iscsi_cmd->write_data_done;
	} else {
		addr = cmd->read_va;
		rkey = cmd->read_stag;
		offset = 0;
	}

	if (isert_prot_cmd(conn, se_cmd)) {
		struct ib_sig_attrs sig_attrs;

		ret = isert_set_sig_attrs(se_cmd, &sig_attrs);
		if (ret)
			return ret;

		WARN_ON_ONCE(offset);
		ret = rdma_rw_ctx_signature_init(&cmd->rw, conn->qp, port_num,
				se_cmd->t_data_sg, se_cmd->t_data_nents,
				se_cmd->t_prot_sg, se_cmd->t_prot_nents,
				&sig_attrs, addr, rkey, dir);
	} else {
		ret = rdma_rw_ctx_init(&cmd->rw, conn->qp, port_num,
				se_cmd->t_data_sg, se_cmd->t_data_nents,
				offset, addr, rkey, dir);
	}

	if (ret < 0) {
		isert_err("Cmd: %p failed to prepare RDMA res\n", cmd);
		return ret;
	}

	cmd->ctx_init_done = true;

rdma_ctx_post:
	ret = rdma_rw_ctx_post(&cmd->rw, conn->qp, port_num, cqe, chain_wr);
	if (ret < 0)
		isert_err("Cmd: %p failed to post RDMA res\n", cmd);
	return ret;
}
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
struct isert_conn {scalar_t__ snd_w_inv; } ;
struct TYPE_3__ {int /*<<< orphan*/  done; } ;
struct iser_tx_desc {int /*<<< orphan*/  num_sge; int /*<<< orphan*/ * tx_sg; TYPE_1__ tx_cqe; } ;
struct isert_cmd {struct iser_tx_desc tx_desc; scalar_t__ inv_rkey; } ;
struct TYPE_4__ {scalar_t__ invalidate_rkey; } ;
struct ib_send_wr {int /*<<< orphan*/  send_flags; int /*<<< orphan*/  num_sge; int /*<<< orphan*/ * sg_list; int /*<<< orphan*/  opcode; TYPE_2__ ex; TYPE_1__* wr_cqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  IB_WR_SEND_WITH_INV ; 
 int /*<<< orphan*/  isert_send_done ; 

__attribute__((used)) static void
isert_init_send_wr(struct isert_conn *isert_conn, struct isert_cmd *isert_cmd,
		   struct ib_send_wr *send_wr)
{
	struct iser_tx_desc *tx_desc = &isert_cmd->tx_desc;

	tx_desc->tx_cqe.done = isert_send_done;
	send_wr->wr_cqe = &tx_desc->tx_cqe;

	if (isert_conn->snd_w_inv && isert_cmd->inv_rkey) {
		send_wr->opcode  = IB_WR_SEND_WITH_INV;
		send_wr->ex.invalidate_rkey = isert_cmd->inv_rkey;
	} else {
		send_wr->opcode = IB_WR_SEND;
	}

	send_wr->sg_list = &tx_desc->tx_sg[0];
	send_wr->num_sge = isert_cmd->tx_desc.num_sge;
	send_wr->send_flags = IB_SEND_SIGNALED;
}
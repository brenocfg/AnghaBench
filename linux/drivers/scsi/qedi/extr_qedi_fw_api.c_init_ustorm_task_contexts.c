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
typedef  int u8 ;
typedef  void* u32 ;
struct TYPE_2__ {int /*<<< orphan*/  reg1_map; } ;
struct ustorm_iscsi_task_st_ctx {TYPE_1__ reg1; void* exp_data_transfer_len; void* rem_rcv_len; } ;
struct e4_ustorm_iscsi_task_ag_ctx {int /*<<< orphan*/  flags2; void* exp_data_acked; } ;

/* Variables and functions */
 int /*<<< orphan*/  E4_USTORM_ISCSI_TASK_AG_CTX_DIF_ERROR_CF_EN ; 
 int /*<<< orphan*/  ISCSI_REG1_NUM_SGES ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le32 (void*) ; 

__attribute__((used)) static
void init_ustorm_task_contexts(struct ustorm_iscsi_task_st_ctx *ustorm_st_cxt,
			struct e4_ustorm_iscsi_task_ag_ctx *ustorm_ag_cxt,
			u32 remaining_recv_len, u32 expected_data_transfer_len,
			u8 num_sges, bool tx_dif_conn_err_en)
{
	u32 val;

	ustorm_st_cxt->rem_rcv_len = cpu_to_le32(remaining_recv_len);
	ustorm_ag_cxt->exp_data_acked = cpu_to_le32(expected_data_transfer_len);
	val = cpu_to_le32(expected_data_transfer_len);
	ustorm_st_cxt->exp_data_transfer_len = val;
	SET_FIELD(ustorm_st_cxt->reg1.reg1_map, ISCSI_REG1_NUM_SGES, num_sges);
	SET_FIELD(ustorm_ag_cxt->flags2,
		  E4_USTORM_ISCSI_TASK_AG_CTX_DIF_ERROR_CF_EN,
		  tx_dif_conn_err_en ? 1 : 0);
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  direct_resp; } ;
struct hinic_cmdq_wqe_lcmd {TYPE_1__ completion; } ;
struct hinic_cmdq_wqe {struct hinic_cmdq_wqe_lcmd wqe_lcmd; } ;
struct hinic_cmdq_buf {int dummy; } ;
typedef  enum hinic_mod_type { ____Placeholder_hinic_mod_type } hinic_mod_type ;
typedef  enum hinic_cmd_ack_type { ____Placeholder_hinic_cmd_ack_type } hinic_cmd_ack_type ;
typedef  enum completion_format { ____Placeholder_completion_format } completion_format ;
typedef  enum cmdq_cmd_type { ____Placeholder_cmdq_cmd_type } cmdq_cmd_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUFDESC_LCMD_LEN ; 
#define  CMDQ_CMD_SYNC_DIRECT_RESP 129 
#define  CMDQ_CMD_SYNC_SGE_RESP 128 
 int COMPLETE_DIRECT ; 
 int COMPLETE_SGE ; 
 int /*<<< orphan*/  DATA_SGE ; 
 int /*<<< orphan*/  cmdq_prepare_wqe_ctrl (struct hinic_cmdq_wqe*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_set_lcmd_bufdesc (struct hinic_cmdq_wqe_lcmd*,struct hinic_cmdq_buf*) ; 
 int /*<<< orphan*/  cmdq_set_sge_completion (TYPE_1__*,struct hinic_cmdq_buf*) ; 

__attribute__((used)) static void cmdq_set_lcmd_wqe(struct hinic_cmdq_wqe *wqe,
			      enum cmdq_cmd_type cmd_type,
			      struct hinic_cmdq_buf *buf_in,
			      struct hinic_cmdq_buf *buf_out, int wrapped,
			      enum hinic_cmd_ack_type ack_type,
			      enum hinic_mod_type mod, u8 cmd, u16 prod_idx)
{
	struct hinic_cmdq_wqe_lcmd *wqe_lcmd = &wqe->wqe_lcmd;
	enum completion_format complete_format;

	switch (cmd_type) {
	case CMDQ_CMD_SYNC_SGE_RESP:
		complete_format = COMPLETE_SGE;
		cmdq_set_sge_completion(&wqe_lcmd->completion, buf_out);
		break;
	case CMDQ_CMD_SYNC_DIRECT_RESP:
		complete_format = COMPLETE_DIRECT;
		wqe_lcmd->completion.direct_resp = 0;
		break;
	}

	cmdq_prepare_wqe_ctrl(wqe, wrapped, ack_type, mod, cmd,
			      prod_idx, complete_format, DATA_SGE,
			      BUFDESC_LCMD_LEN);

	cmdq_set_lcmd_bufdesc(wqe_lcmd, buf_in);
}
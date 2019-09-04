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
typedef  int /*<<< orphan*/  u32 ;
struct hinic_ctrl {scalar_t__ ctrl_info; } ;
struct hinic_cmdq_wqe_scmd {struct hinic_ctrl ctrl; } ;
struct hinic_cmdq_wqe_lcmd {struct hinic_ctrl ctrl; } ;
struct hinic_cmdq_direct_wqe {struct hinic_cmdq_wqe_scmd wqe_scmd; } ;
struct hinic_cmdq_wqe {struct hinic_cmdq_direct_wqe direct_wqe; struct hinic_cmdq_wqe_lcmd wqe_lcmd; } ;
struct hinic_cmdq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  header_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFDESC_LEN ; 
 TYPE_1__* CMDQ_WQE_HEADER (struct hinic_cmdq_wqe*) ; 
 unsigned int HINIC_CMDQ_WQE_HEADER_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int WQE_LCMD_SIZE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int cmdq_wqe_size_from_bdlen (unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void clear_wqe_complete_bit(struct hinic_cmdq *cmdq,
				   struct hinic_cmdq_wqe *wqe)
{
	u32 header_info = be32_to_cpu(CMDQ_WQE_HEADER(wqe)->header_info);
	unsigned int bufdesc_len, wqe_size;
	struct hinic_ctrl *ctrl;

	bufdesc_len = HINIC_CMDQ_WQE_HEADER_GET(header_info, BUFDESC_LEN);
	wqe_size = cmdq_wqe_size_from_bdlen(bufdesc_len);
	if (wqe_size == WQE_LCMD_SIZE) {
		struct hinic_cmdq_wqe_lcmd *wqe_lcmd = &wqe->wqe_lcmd;

		ctrl = &wqe_lcmd->ctrl;
	} else {
		struct hinic_cmdq_direct_wqe *direct_wqe = &wqe->direct_wqe;
		struct hinic_cmdq_wqe_scmd *wqe_scmd;

		wqe_scmd = &direct_wqe->wqe_scmd;
		ctrl = &wqe_scmd->ctrl;
	}

	/* clear HW busy bit */
	ctrl->ctrl_info = 0;

	wmb();  /* verify wqe is clear */
}
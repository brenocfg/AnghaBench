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
typedef  int u64 ;
typedef  int u32 ;
struct i40iw_update_sds_info {int cnt; int hmc_fn_id; TYPE_1__* entry; } ;
struct i40iw_dma_mem {scalar_t__ pa; scalar_t__ va; } ;
struct i40iw_sc_cqp {int polarity; int /*<<< orphan*/  dev; struct i40iw_dma_mem sdbuf; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {int cmd; int data; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_UPESD_ENTRY_COUNT ; 
 int /*<<< orphan*/  I40IW_CQPSQ_UPESD_ENTRY_VALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_UPESD_HMCFNID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_UPESD_SDCMD ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int /*<<< orphan*/  I40IW_CQP_INIT_WQE (int*) ; 
 int I40IW_CQP_OP_UPDATE_PE_SDS ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_RING_FULL ; 
 int I40IW_UPDATE_SD_BUF_SIZE ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe_idx (struct i40iw_sc_cqp*,int,int*) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 

__attribute__((used)) static enum i40iw_status_code cqp_sds_wqe_fill(struct i40iw_sc_cqp *cqp,
					       struct i40iw_update_sds_info *info,
					       u64 scratch)
{
	u64 data;
	u64 header;
	u64 *wqe;
	int mem_entries, wqe_entries;
	struct i40iw_dma_mem *sdbuf = &cqp->sdbuf;
	u64 offset;
	u32 wqe_idx;

	wqe = i40iw_sc_cqp_get_next_send_wqe_idx(cqp, scratch, &wqe_idx);
	if (!wqe)
		return I40IW_ERR_RING_FULL;

	I40IW_CQP_INIT_WQE(wqe);
	wqe_entries = (info->cnt > 3) ? 3 : info->cnt;
	mem_entries = info->cnt - wqe_entries;

	header = LS_64(I40IW_CQP_OP_UPDATE_PE_SDS, I40IW_CQPSQ_OPCODE) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID) |
		 LS_64(mem_entries, I40IW_CQPSQ_UPESD_ENTRY_COUNT);

	if (mem_entries) {
		offset = wqe_idx * I40IW_UPDATE_SD_BUF_SIZE;
		memcpy((char *)sdbuf->va + offset, &info->entry[3],
		       mem_entries << 4);
		data = (u64)sdbuf->pa + offset;
	} else {
		data = 0;
	}
	data |= LS_64(info->hmc_fn_id, I40IW_CQPSQ_UPESD_HMCFNID);

	set_64bit_val(wqe, 16, data);

	switch (wqe_entries) {
	case 3:
		set_64bit_val(wqe, 48,
			      (LS_64(info->entry[2].cmd, I40IW_CQPSQ_UPESD_SDCMD) |
					LS_64(1, I40IW_CQPSQ_UPESD_ENTRY_VALID)));

		set_64bit_val(wqe, 56, info->entry[2].data);
		/* fallthrough */
	case 2:
		set_64bit_val(wqe, 32,
			      (LS_64(info->entry[1].cmd, I40IW_CQPSQ_UPESD_SDCMD) |
					LS_64(1, I40IW_CQPSQ_UPESD_ENTRY_VALID)));

		set_64bit_val(wqe, 40, info->entry[1].data);
		/* fallthrough */
	case 1:
		set_64bit_val(wqe, 0,
			      LS_64(info->entry[0].cmd, I40IW_CQPSQ_UPESD_SDCMD));

		set_64bit_val(wqe, 8, info->entry[0].data);
		break;
	default:
		break;
	}

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "UPDATE_PE_SDS WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);
	return 0;
}
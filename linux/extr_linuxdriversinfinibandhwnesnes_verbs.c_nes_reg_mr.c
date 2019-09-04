#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint ;
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct nes_root_vpbl {scalar_t__ pbl_pbase; int /*<<< orphan*/  pbl_vbase; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct nes_pd {int pd_id; } ;
struct nes_hw_cqp_wqe {int /*<<< orphan*/ * wqe_words; } ;
struct nes_device {int /*<<< orphan*/  pcidev; struct nes_adapter* nesadapter; } ;
struct nes_cqp_request {int waiting; scalar_t__ request_done; int major_code; int /*<<< orphan*/  minor_code; int /*<<< orphan*/  waitq; int /*<<< orphan*/  refcount; struct nes_hw_cqp_wqe cqp_wqe; } ;
struct nes_adapter {int free_256pbl; int free_4kpbl; int max_4kpbl; int /*<<< orphan*/  pbl_lock; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ETIME ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_MW_BIND ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int NES_CQP_REGISTER_STAG ; 
 int NES_CQP_STAG_MR ; 
 int NES_CQP_STAG_PBL_BLK_SIZE ; 
 int NES_CQP_STAG_REM_ACC_EN ; 
 int NES_CQP_STAG_RIGHTS_LOCAL_READ ; 
 int NES_CQP_STAG_RIGHTS_LOCAL_WRITE ; 
 int NES_CQP_STAG_RIGHTS_REMOTE_READ ; 
 int NES_CQP_STAG_RIGHTS_REMOTE_WRITE ; 
 int NES_CQP_STAG_RIGHTS_WINDOW_BIND ; 
 int NES_CQP_STAG_VA_TO ; 
 size_t NES_CQP_STAG_WQE_LEN_HIGH_PD_IDX ; 
 size_t NES_CQP_STAG_WQE_LEN_LOW_IDX ; 
 int /*<<< orphan*/  NES_CQP_STAG_WQE_PA_LOW_IDX ; 
 size_t NES_CQP_STAG_WQE_PBL_BLK_COUNT_IDX ; 
 size_t NES_CQP_STAG_WQE_PBL_LEN_IDX ; 
 size_t NES_CQP_STAG_WQE_STAG_IDX ; 
 int /*<<< orphan*/  NES_CQP_STAG_WQE_VA_LOW_IDX ; 
 size_t NES_CQP_WQE_OPCODE_IDX ; 
 int /*<<< orphan*/  NES_DBG_MR ; 
 int /*<<< orphan*/  NES_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nes_fill_init_cqp_wqe (struct nes_hw_cqp_wqe*,struct nes_device*) ; 
 int /*<<< orphan*/  nes_free_cqp_request (struct nes_device*,struct nes_cqp_request*) ; 
 struct nes_cqp_request* nes_get_cqp_request (struct nes_device*) ; 
 int /*<<< orphan*/  nes_post_cqp_request (struct nes_device*,struct nes_cqp_request*) ; 
 int /*<<< orphan*/  nes_put_cqp_request (struct nes_device*,struct nes_cqp_request*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int root_256 (struct nes_device*,struct nes_root_vpbl*,struct nes_root_vpbl*,int) ; 
 int /*<<< orphan*/  set_wqe_32bit_value (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  set_wqe_64bit_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nes_reg_mr(struct nes_device *nesdev, struct nes_pd *nespd,
		u32 stag, u64 region_length, struct nes_root_vpbl *root_vpbl,
		dma_addr_t single_buffer, u16 pbl_count_4k,
		u16 residual_page_count_4k, int acc, u64 *iova_start,
		u16 *actual_pbl_cnt, u8 *used_4k_pbls)
{
	struct nes_hw_cqp_wqe *cqp_wqe;
	struct nes_cqp_request *cqp_request;
	unsigned long flags;
	int ret;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	uint pg_cnt = 0;
	u16 pbl_count_256 = 0;
	u16 pbl_count = 0;
	u8  use_256_pbls = 0;
	u8  use_4k_pbls = 0;
	u16 use_two_level = (pbl_count_4k > 1) ? 1 : 0;
	struct nes_root_vpbl new_root = { 0, NULL, NULL };
	u32 opcode = 0;
	u16 major_code;

	/* Register the region with the adapter */
	cqp_request = nes_get_cqp_request(nesdev);
	if (cqp_request == NULL) {
		nes_debug(NES_DBG_MR, "Failed to get a cqp_request.\n");
		return -ENOMEM;
	}
	cqp_request->waiting = 1;
	cqp_wqe = &cqp_request->cqp_wqe;

	if (pbl_count_4k) {
		spin_lock_irqsave(&nesadapter->pbl_lock, flags);

		pg_cnt = ((pbl_count_4k - 1) * 512) + residual_page_count_4k;
		pbl_count_256 = (pg_cnt + 31) / 32;
		if (pg_cnt <= 32) {
			if (pbl_count_256 <= nesadapter->free_256pbl)
				use_256_pbls = 1;
			else if (pbl_count_4k <= nesadapter->free_4kpbl)
				use_4k_pbls = 1;
		} else if (pg_cnt <= 2048) {
			if (((pbl_count_4k + use_two_level) <= nesadapter->free_4kpbl) &&
			    (nesadapter->free_4kpbl > (nesadapter->max_4kpbl >> 1))) {
				use_4k_pbls = 1;
			} else if ((pbl_count_256 + 1) <= nesadapter->free_256pbl) {
				use_256_pbls = 1;
				use_two_level = 1;
			} else if ((pbl_count_4k + use_two_level) <= nesadapter->free_4kpbl) {
				use_4k_pbls = 1;
			}
		} else {
			if ((pbl_count_4k + 1) <= nesadapter->free_4kpbl)
				use_4k_pbls = 1;
		}

		if (use_256_pbls) {
			pbl_count = pbl_count_256;
			nesadapter->free_256pbl -= pbl_count + use_two_level;
		} else if (use_4k_pbls) {
			pbl_count =  pbl_count_4k;
			nesadapter->free_4kpbl -= pbl_count + use_two_level;
		} else {
			spin_unlock_irqrestore(&nesadapter->pbl_lock, flags);
			nes_debug(NES_DBG_MR, "Out of Pbls\n");
			nes_free_cqp_request(nesdev, cqp_request);
			return -ENOMEM;
		}

		spin_unlock_irqrestore(&nesadapter->pbl_lock, flags);
	}

	if (use_256_pbls && use_two_level) {
		if (root_256(nesdev, root_vpbl, &new_root, pbl_count_4k) == 1) {
			if (new_root.pbl_pbase != 0)
				root_vpbl = &new_root;
		} else {
			spin_lock_irqsave(&nesadapter->pbl_lock, flags);
			nesadapter->free_256pbl += pbl_count_256 + use_two_level;
			use_256_pbls = 0;

			if (pbl_count_4k == 1)
				use_two_level = 0;
			pbl_count = pbl_count_4k;

			if ((pbl_count_4k + use_two_level) <= nesadapter->free_4kpbl) {
				nesadapter->free_4kpbl -= pbl_count + use_two_level;
				use_4k_pbls = 1;
			}
			spin_unlock_irqrestore(&nesadapter->pbl_lock, flags);

			if (use_4k_pbls == 0)
				return -ENOMEM;
		}
	}

	opcode = NES_CQP_REGISTER_STAG | NES_CQP_STAG_RIGHTS_LOCAL_READ |
					NES_CQP_STAG_VA_TO | NES_CQP_STAG_MR;
	if (acc & IB_ACCESS_LOCAL_WRITE)
		opcode |= NES_CQP_STAG_RIGHTS_LOCAL_WRITE;
	if (acc & IB_ACCESS_REMOTE_WRITE)
		opcode |= NES_CQP_STAG_RIGHTS_REMOTE_WRITE | NES_CQP_STAG_REM_ACC_EN;
	if (acc & IB_ACCESS_REMOTE_READ)
		opcode |= NES_CQP_STAG_RIGHTS_REMOTE_READ | NES_CQP_STAG_REM_ACC_EN;
	if (acc & IB_ACCESS_MW_BIND)
		opcode |= NES_CQP_STAG_RIGHTS_WINDOW_BIND | NES_CQP_STAG_REM_ACC_EN;

	nes_fill_init_cqp_wqe(cqp_wqe, nesdev);
	set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_WQE_OPCODE_IDX, opcode);
	set_wqe_64bit_value(cqp_wqe->wqe_words, NES_CQP_STAG_WQE_VA_LOW_IDX, *iova_start);
	set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_STAG_WQE_LEN_LOW_IDX, region_length);

	cqp_wqe->wqe_words[NES_CQP_STAG_WQE_LEN_HIGH_PD_IDX] =
			cpu_to_le32((u32)(region_length >> 8) & 0xff000000);
	cqp_wqe->wqe_words[NES_CQP_STAG_WQE_LEN_HIGH_PD_IDX] |=
			cpu_to_le32(nespd->pd_id & 0x00007fff);
	set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_STAG_WQE_STAG_IDX, stag);

	if (pbl_count == 0) {
		set_wqe_64bit_value(cqp_wqe->wqe_words, NES_CQP_STAG_WQE_PA_LOW_IDX, single_buffer);
	} else {
		set_wqe_64bit_value(cqp_wqe->wqe_words, NES_CQP_STAG_WQE_PA_LOW_IDX, root_vpbl->pbl_pbase);
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_STAG_WQE_PBL_BLK_COUNT_IDX, pbl_count);
		set_wqe_32bit_value(cqp_wqe->wqe_words, NES_CQP_STAG_WQE_PBL_LEN_IDX, (pg_cnt * 8));

		if (use_4k_pbls)
			cqp_wqe->wqe_words[NES_CQP_WQE_OPCODE_IDX] |= cpu_to_le32(NES_CQP_STAG_PBL_BLK_SIZE);
	}
	barrier();

	atomic_set(&cqp_request->refcount, 2);
	nes_post_cqp_request(nesdev, cqp_request);

	/* Wait for CQP */
	ret = wait_event_timeout(cqp_request->waitq, (0 != cqp_request->request_done),
			NES_EVENT_TIMEOUT);
	nes_debug(NES_DBG_MR, "Register STag 0x%08X completed, wait_event_timeout ret = %u,"
			" CQP Major:Minor codes = 0x%04X:0x%04X.\n",
			stag, ret, cqp_request->major_code, cqp_request->minor_code);
	major_code = cqp_request->major_code;
	nes_put_cqp_request(nesdev, cqp_request);

	if ((!ret || major_code) && pbl_count != 0) {
		spin_lock_irqsave(&nesadapter->pbl_lock, flags);
		if (use_256_pbls)
			nesadapter->free_256pbl += pbl_count + use_two_level;
		else if (use_4k_pbls)
			nesadapter->free_4kpbl += pbl_count + use_two_level;
		spin_unlock_irqrestore(&nesadapter->pbl_lock, flags);
	}
	if (new_root.pbl_pbase)
		pci_free_consistent(nesdev->pcidev, 512, new_root.pbl_vbase,
				    new_root.pbl_pbase);

	if (!ret)
		return -ETIME;
	else if (major_code)
		return -EIO;

	*actual_pbl_cnt = pbl_count + use_two_level;
	*used_4k_pbls = use_4k_pbls;
	return 0;
}
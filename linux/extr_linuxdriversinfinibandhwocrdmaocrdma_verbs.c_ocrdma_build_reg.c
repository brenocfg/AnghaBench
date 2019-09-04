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
typedef  int u64 ;
typedef  int u32 ;
struct ocrdma_qp {int dummy; } ;
struct ocrdma_pbl {struct ocrdma_pbe* va; } ;
struct ocrdma_pbe {void* pa_hi; void* pa_lo; } ;
struct TYPE_4__ {int pbl_size; struct ocrdma_pbl* pbl_table; } ;
struct TYPE_3__ {int iova; int /*<<< orphan*/  page_size; int /*<<< orphan*/  length; } ;
struct ocrdma_mr {int* pages; int npages; TYPE_2__ hwmr; TYPE_1__ ibmr; } ;
struct ocrdma_hdr_wqe {int cw; int /*<<< orphan*/  total_len; int /*<<< orphan*/  lkey; int /*<<< orphan*/  rsvd_lkey_flags; } ;
struct ocrdma_ewqe_fr {int va_lo; int fbo_lo; int num_sges; int /*<<< orphan*/  size_sge; void* fbo_hi; void* va_hi; } ;
struct ib_reg_wr {int access; int /*<<< orphan*/  key; int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int OCRDMA_FR_MR ; 
 int /*<<< orphan*/  OCRDMA_LKEY_FLAG_LOCAL_WR ; 
 int /*<<< orphan*/  OCRDMA_LKEY_FLAG_REMOTE_RD ; 
 int /*<<< orphan*/  OCRDMA_LKEY_FLAG_REMOTE_WR ; 
 int /*<<< orphan*/  OCRDMA_WQE_ALIGN_BYTES ; 
 int OCRDMA_WQE_OPCODE_SHIFT ; 
 int OCRDMA_WQE_SIZE_SHIFT ; 
 int OCRDMA_WQE_STRIDE ; 
 int PAGE_MASK ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  get_encoded_page_size (int /*<<< orphan*/ ) ; 
 struct ocrdma_mr* get_ocrdma_mr (int /*<<< orphan*/ ) ; 
 int roundup (int,int /*<<< orphan*/ ) ; 
 void* upper_32_bits (int) ; 

__attribute__((used)) static int ocrdma_build_reg(struct ocrdma_qp *qp,
			    struct ocrdma_hdr_wqe *hdr,
			    const struct ib_reg_wr *wr)
{
	u64 fbo;
	struct ocrdma_ewqe_fr *fast_reg = (struct ocrdma_ewqe_fr *)(hdr + 1);
	struct ocrdma_mr *mr = get_ocrdma_mr(wr->mr);
	struct ocrdma_pbl *pbl_tbl = mr->hwmr.pbl_table;
	struct ocrdma_pbe *pbe;
	u32 wqe_size = sizeof(*fast_reg) + sizeof(*hdr);
	int num_pbes = 0, i;

	wqe_size = roundup(wqe_size, OCRDMA_WQE_ALIGN_BYTES);

	hdr->cw |= (OCRDMA_FR_MR << OCRDMA_WQE_OPCODE_SHIFT);
	hdr->cw |= ((wqe_size / OCRDMA_WQE_STRIDE) << OCRDMA_WQE_SIZE_SHIFT);

	if (wr->access & IB_ACCESS_LOCAL_WRITE)
		hdr->rsvd_lkey_flags |= OCRDMA_LKEY_FLAG_LOCAL_WR;
	if (wr->access & IB_ACCESS_REMOTE_WRITE)
		hdr->rsvd_lkey_flags |= OCRDMA_LKEY_FLAG_REMOTE_WR;
	if (wr->access & IB_ACCESS_REMOTE_READ)
		hdr->rsvd_lkey_flags |= OCRDMA_LKEY_FLAG_REMOTE_RD;
	hdr->lkey = wr->key;
	hdr->total_len = mr->ibmr.length;

	fbo = mr->ibmr.iova - mr->pages[0];

	fast_reg->va_hi = upper_32_bits(mr->ibmr.iova);
	fast_reg->va_lo = (u32) (mr->ibmr.iova & 0xffffffff);
	fast_reg->fbo_hi = upper_32_bits(fbo);
	fast_reg->fbo_lo = (u32) fbo & 0xffffffff;
	fast_reg->num_sges = mr->npages;
	fast_reg->size_sge = get_encoded_page_size(mr->ibmr.page_size);

	pbe = pbl_tbl->va;
	for (i = 0; i < mr->npages; i++) {
		u64 buf_addr = mr->pages[i];

		pbe->pa_lo = cpu_to_le32((u32) (buf_addr & PAGE_MASK));
		pbe->pa_hi = cpu_to_le32((u32) upper_32_bits(buf_addr));
		num_pbes += 1;
		pbe++;

		/* if the pbl is full storing the pbes,
		 * move to next pbl.
		*/
		if (num_pbes == (mr->hwmr.pbl_size/sizeof(u64))) {
			pbl_tbl++;
			pbe = (struct ocrdma_pbe *)pbl_tbl->va;
		}
	}

	return 0;
}
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
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct pci_dev {int dummy; } ;
struct bnxt_qplib_sg_info {int npages; int nmap; struct scatterlist* sglist; } ;
struct bnxt_qplib_hwq {size_t level; int is_user; int max_elements; int element_size; int* pbl_dma_ptr; TYPE_1__* pbl; scalar_t__ pbl_ptr; scalar_t__ cons; scalar_t__ prod; int /*<<< orphan*/  lock; struct pci_dev* pdev; } ;
typedef  enum bnxt_qplib_hwq_type { ____Placeholder_bnxt_qplib_hwq_type } bnxt_qplib_hwq_type ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int* pg_map_arr; int pg_count; scalar_t__ pg_arr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int HWQ_TYPE_L2_CMPL ; 
 int HWQ_TYPE_QUEUE ; 
 int MAX_PBL_LVL_0_PGS ; 
 int MAX_PBL_LVL_1_PGS ; 
 int MAX_PBL_LVL_1_PGS_FOR_LVL_2 ; 
 size_t PBL_LVL_0 ; 
 size_t PBL_LVL_1 ; 
 size_t PBL_LVL_2 ; 
 size_t PBL_LVL_MAX ; 
 size_t PTR_IDX (int) ; 
 size_t PTR_PG (int) ; 
 int PTU_PDE_VALID ; 
 int PTU_PTE_LAST ; 
 int PTU_PTE_NEXT_TO_LAST ; 
 int PTU_PTE_VALID ; 
 int __alloc_pbl (struct pci_dev*,TYPE_1__*,struct scatterlist*,int,int,int) ; 
 int /*<<< orphan*/  bnxt_qplib_free_hwq (struct pci_dev*,struct bnxt_qplib_hwq*) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int bnxt_qplib_alloc_init_hwq(struct pci_dev *pdev, struct bnxt_qplib_hwq *hwq,
			      struct bnxt_qplib_sg_info *sg_info,
			      u32 *elements, u32 element_size, u32 aux,
			      u32 pg_size, enum bnxt_qplib_hwq_type hwq_type)
{
	u32 pages, maps, slots, size, aux_pages = 0, aux_size = 0;
	dma_addr_t *src_phys_ptr, **dst_virt_ptr;
	struct scatterlist *sghead = NULL;
	int i, rc;

	hwq->level = PBL_LVL_MAX;

	slots = roundup_pow_of_two(*elements);
	if (aux) {
		aux_size = roundup_pow_of_two(aux);
		aux_pages = (slots * aux_size) / pg_size;
		if ((slots * aux_size) % pg_size)
			aux_pages++;
	}
	size = roundup_pow_of_two(element_size);

	if (sg_info)
		sghead = sg_info->sglist;

	if (!sghead) {
		hwq->is_user = false;
		pages = (slots * size) / pg_size + aux_pages;
		if ((slots * size) % pg_size)
			pages++;
		if (!pages)
			return -EINVAL;
		maps = 0;
	} else {
		hwq->is_user = true;
		pages = sg_info->npages;
		maps = sg_info->nmap;
	}

	/* Alloc the 1st memory block; can be a PDL/PTL/PBL */
	if (sghead && (pages == MAX_PBL_LVL_0_PGS))
		rc = __alloc_pbl(pdev, &hwq->pbl[PBL_LVL_0], sghead,
				 pages, maps, pg_size);
	else
		rc = __alloc_pbl(pdev, &hwq->pbl[PBL_LVL_0], NULL,
				 1, 0, pg_size);
	if (rc)
		goto fail;

	hwq->level = PBL_LVL_0;

	if (pages > MAX_PBL_LVL_0_PGS) {
		if (pages > MAX_PBL_LVL_1_PGS) {
			/* 2 levels of indirection */
			rc = __alloc_pbl(pdev, &hwq->pbl[PBL_LVL_1], NULL,
					 MAX_PBL_LVL_1_PGS_FOR_LVL_2,
					 0, pg_size);
			if (rc)
				goto fail;
			/* Fill in lvl0 PBL */
			dst_virt_ptr =
				(dma_addr_t **)hwq->pbl[PBL_LVL_0].pg_arr;
			src_phys_ptr = hwq->pbl[PBL_LVL_1].pg_map_arr;
			for (i = 0; i < hwq->pbl[PBL_LVL_1].pg_count; i++)
				dst_virt_ptr[PTR_PG(i)][PTR_IDX(i)] =
					src_phys_ptr[i] | PTU_PDE_VALID;
			hwq->level = PBL_LVL_1;

			rc = __alloc_pbl(pdev, &hwq->pbl[PBL_LVL_2], sghead,
					 pages, maps, pg_size);
			if (rc)
				goto fail;

			/* Fill in lvl1 PBL */
			dst_virt_ptr =
				(dma_addr_t **)hwq->pbl[PBL_LVL_1].pg_arr;
			src_phys_ptr = hwq->pbl[PBL_LVL_2].pg_map_arr;
			for (i = 0; i < hwq->pbl[PBL_LVL_2].pg_count; i++) {
				dst_virt_ptr[PTR_PG(i)][PTR_IDX(i)] =
					src_phys_ptr[i] | PTU_PTE_VALID;
			}
			if (hwq_type == HWQ_TYPE_QUEUE) {
				/* Find the last pg of the size */
				i = hwq->pbl[PBL_LVL_2].pg_count;
				dst_virt_ptr[PTR_PG(i - 1)][PTR_IDX(i - 1)] |=
								  PTU_PTE_LAST;
				if (i > 1)
					dst_virt_ptr[PTR_PG(i - 2)]
						    [PTR_IDX(i - 2)] |=
						    PTU_PTE_NEXT_TO_LAST;
			}
			hwq->level = PBL_LVL_2;
		} else {
			u32 flag = hwq_type == HWQ_TYPE_L2_CMPL ? 0 :
						PTU_PTE_VALID;

			/* 1 level of indirection */
			rc = __alloc_pbl(pdev, &hwq->pbl[PBL_LVL_1], sghead,
					 pages, maps, pg_size);
			if (rc)
				goto fail;
			/* Fill in lvl0 PBL */
			dst_virt_ptr =
				(dma_addr_t **)hwq->pbl[PBL_LVL_0].pg_arr;
			src_phys_ptr = hwq->pbl[PBL_LVL_1].pg_map_arr;
			for (i = 0; i < hwq->pbl[PBL_LVL_1].pg_count; i++) {
				dst_virt_ptr[PTR_PG(i)][PTR_IDX(i)] =
					src_phys_ptr[i] | flag;
			}
			if (hwq_type == HWQ_TYPE_QUEUE) {
				/* Find the last pg of the size */
				i = hwq->pbl[PBL_LVL_1].pg_count;
				dst_virt_ptr[PTR_PG(i - 1)][PTR_IDX(i - 1)] |=
								  PTU_PTE_LAST;
				if (i > 1)
					dst_virt_ptr[PTR_PG(i - 2)]
						    [PTR_IDX(i - 2)] |=
						    PTU_PTE_NEXT_TO_LAST;
			}
			hwq->level = PBL_LVL_1;
		}
	}
	hwq->pdev = pdev;
	spin_lock_init(&hwq->lock);
	hwq->prod = 0;
	hwq->cons = 0;
	*elements = hwq->max_elements = slots;
	hwq->element_size = size;

	/* For direct access to the elements */
	hwq->pbl_ptr = hwq->pbl[hwq->level].pg_arr;
	hwq->pbl_dma_ptr = hwq->pbl[hwq->level].pg_map_arr;

	return 0;

fail:
	bnxt_qplib_free_hwq(pdev, hwq);
	return -ENOMEM;
}
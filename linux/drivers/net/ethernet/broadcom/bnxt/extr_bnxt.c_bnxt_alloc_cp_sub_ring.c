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
struct bnxt_ring_mem_info {void** pg_arr; int /*<<< orphan*/  flags; int /*<<< orphan*/  dma_arr; int /*<<< orphan*/  page_size; int /*<<< orphan*/  nr_pages; } ;
struct bnxt_ring_struct {struct bnxt_ring_mem_info ring_mem; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/  cp_desc_mapping; scalar_t__ cp_desc_ring; struct bnxt_ring_struct cp_ring_struct; } ;
struct bnxt {int /*<<< orphan*/  cp_nr_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_RMEM_RING_PTE_FLAG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HW_CMPD_RING_SIZE ; 
 int bnxt_alloc_ring (struct bnxt*,struct bnxt_ring_mem_info*) ; 
 int /*<<< orphan*/  bnxt_free_ring (struct bnxt*,struct bnxt_ring_mem_info*) ; 
 int /*<<< orphan*/  kfree (struct bnxt_cp_ring_info*) ; 
 struct bnxt_cp_ring_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bnxt_cp_ring_info *bnxt_alloc_cp_sub_ring(struct bnxt *bp)
{
	struct bnxt_ring_mem_info *rmem;
	struct bnxt_ring_struct *ring;
	struct bnxt_cp_ring_info *cpr;
	int rc;

	cpr = kzalloc(sizeof(*cpr), GFP_KERNEL);
	if (!cpr)
		return NULL;

	ring = &cpr->cp_ring_struct;
	rmem = &ring->ring_mem;
	rmem->nr_pages = bp->cp_nr_pages;
	rmem->page_size = HW_CMPD_RING_SIZE;
	rmem->pg_arr = (void **)cpr->cp_desc_ring;
	rmem->dma_arr = cpr->cp_desc_mapping;
	rmem->flags = BNXT_RMEM_RING_PTE_FLAG;
	rc = bnxt_alloc_ring(bp, rmem);
	if (rc) {
		bnxt_free_ring(bp, rmem);
		kfree(cpr);
		cpr = NULL;
	}
	return cpr;
}
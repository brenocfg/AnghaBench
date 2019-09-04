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
struct slic_stat_queue {unsigned int active_array; size_t done_idx; int len; int /*<<< orphan*/ * paddr; struct slic_stat_desc** descs; } ;
struct slic_stat_desc {scalar_t__ status; scalar_t__ hnd; } ;
struct slic_device {struct slic_stat_queue stq; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int SLIC_INVALID_STAT_DESC_IDX ; 
 int SLIC_NUM_STAT_DESC_ARRAYS ; 
 int /*<<< orphan*/  SLIC_REG_RBAR ; 
 int le32_to_cpu (scalar_t__) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slic_flush_write (struct slic_device*) ; 
 size_t slic_next_queue_idx (size_t,int) ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int slic_next_compl_idx(struct slic_device *sdev)
{
	struct slic_stat_queue *stq = &sdev->stq;
	unsigned int active = stq->active_array;
	struct slic_stat_desc *descs;
	struct slic_stat_desc *stat;
	unsigned int idx;

	descs = stq->descs[active];
	stat = &descs[stq->done_idx];

	if (!stat->status)
		return SLIC_INVALID_STAT_DESC_IDX;

	idx = (le32_to_cpu(stat->hnd) & 0xffff) - 1;
	/* reset desc */
	stat->hnd = 0;
	stat->status = 0;

	stq->done_idx = slic_next_queue_idx(stq->done_idx, stq->len);
	/* check for wraparound */
	if (!stq->done_idx) {
		dma_addr_t paddr = stq->paddr[active];

		slic_write(sdev, SLIC_REG_RBAR, lower_32_bits(paddr) |
						stq->len);
		/* make sure new status descriptors are immediately available */
		slic_flush_write(sdev);
		active++;
		active &= (SLIC_NUM_STAT_DESC_ARRAYS - 1);
		stq->active_array = active;
	}
	return idx;
}
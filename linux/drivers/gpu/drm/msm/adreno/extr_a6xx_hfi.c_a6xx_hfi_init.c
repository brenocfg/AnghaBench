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
typedef  int u64 ;
struct a6xx_hfi_queue_table_header {int size; int qhdr0_offset; int qhdr_size; int num_queues; int active_queues; scalar_t__ version; } ;
struct a6xx_hfi_queue_header {int size; int qhdr0_offset; int qhdr_size; int num_queues; int active_queues; scalar_t__ version; } ;
struct a6xx_gmu_bo {int iova; struct a6xx_hfi_queue_table_header* virt; } ;
struct a6xx_gmu {int /*<<< orphan*/ * queues; struct a6xx_gmu_bo* hfi; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int SZ_4K ; 
 int /*<<< orphan*/  a6xx_hfi_queue_init (int /*<<< orphan*/ *,struct a6xx_hfi_queue_table_header*,struct a6xx_hfi_queue_table_header*,int,int) ; 

void a6xx_hfi_init(struct a6xx_gmu *gmu)
{
	struct a6xx_gmu_bo *hfi = gmu->hfi;
	struct a6xx_hfi_queue_table_header *table = hfi->virt;
	struct a6xx_hfi_queue_header *headers = hfi->virt + sizeof(*table);
	u64 offset;
	int table_size;

	/*
	 * The table size is the size of the table header plus all of the queue
	 * headers
	 */
	table_size = sizeof(*table);
	table_size += (ARRAY_SIZE(gmu->queues) *
		sizeof(struct a6xx_hfi_queue_header));

	table->version = 0;
	table->size = table_size;
	/* First queue header is located immediately after the table header */
	table->qhdr0_offset = sizeof(*table) >> 2;
	table->qhdr_size = sizeof(struct a6xx_hfi_queue_header) >> 2;
	table->num_queues = ARRAY_SIZE(gmu->queues);
	table->active_queues = ARRAY_SIZE(gmu->queues);

	/* Command queue */
	offset = SZ_4K;
	a6xx_hfi_queue_init(&gmu->queues[0], &headers[0], hfi->virt + offset,
		hfi->iova + offset, 0);

	/* GMU response queue */
	offset += SZ_4K;
	a6xx_hfi_queue_init(&gmu->queues[1], &headers[1], hfi->virt + offset,
		hfi->iova + offset, 4);
}
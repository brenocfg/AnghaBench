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
struct ionic_cq_info {void* cq_desc; } ;
struct ionic_cq {unsigned int num_descs; unsigned int desc_size; struct ionic_cq_info* info; int /*<<< orphan*/  base_pa; void* base; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */

void ionic_cq_map(struct ionic_cq *cq, void *base, dma_addr_t base_pa)
{
	struct ionic_cq_info *cur;
	unsigned int i;

	cq->base = base;
	cq->base_pa = base_pa;

	for (i = 0, cur = cq->info; i < cq->num_descs; i++, cur++)
		cur->cq_desc = base + (i * cq->desc_size);
}
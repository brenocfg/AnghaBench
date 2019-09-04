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
struct sdma_mmu_node {TYPE_1__* pq; scalar_t__ npages; int /*<<< orphan*/  pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  n_locked; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpin_vector_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void unpin_sdma_pages(struct sdma_mmu_node *node)
{
	if (node->npages) {
		unpin_vector_pages(node->pq->mm, node->pages, 0, node->npages);
		atomic_sub(node->npages, &node->pq->n_locked);
	}
}
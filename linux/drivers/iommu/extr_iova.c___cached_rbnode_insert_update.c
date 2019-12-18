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
struct iova_domain {scalar_t__ dma_32bit_pfn; int /*<<< orphan*/ * cached_node; int /*<<< orphan*/ * cached32_node; } ;
struct iova {scalar_t__ pfn_hi; int /*<<< orphan*/  node; } ;

/* Variables and functions */

__attribute__((used)) static void
__cached_rbnode_insert_update(struct iova_domain *iovad, struct iova *new)
{
	if (new->pfn_hi < iovad->dma_32bit_pfn)
		iovad->cached32_node = &new->node;
	else
		iovad->cached_node = &new->node;
}
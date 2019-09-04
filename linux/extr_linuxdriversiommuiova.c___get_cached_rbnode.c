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
struct rb_node {int dummy; } ;
struct iova_domain {unsigned long dma_32bit_pfn; struct rb_node* cached_node; struct rb_node* cached32_node; } ;

/* Variables and functions */

__attribute__((used)) static struct rb_node *
__get_cached_rbnode(struct iova_domain *iovad, unsigned long limit_pfn)
{
	if (limit_pfn <= iovad->dma_32bit_pfn)
		return iovad->cached32_node;

	return iovad->cached_node;
}
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
struct mmu_rb_node {unsigned long addr; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 

__attribute__((used)) static unsigned long mmu_node_start(struct mmu_rb_node *node)
{
	return node->addr & PAGE_MASK;
}
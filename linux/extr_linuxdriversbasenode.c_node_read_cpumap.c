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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct node {TYPE_1__ dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NR_CPUS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumap_print_to_pagebuf (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 struct node* to_node (struct device*) ; 

__attribute__((used)) static ssize_t node_read_cpumap(struct device *dev, bool list, char *buf)
{
	ssize_t n;
	cpumask_var_t mask;
	struct node *node_dev = to_node(dev);

	/* 2008/04/07: buf currently PAGE_SIZE, need 9 chars per 32 bits. */
	BUILD_BUG_ON((NR_CPUS/32 * 9) > (PAGE_SIZE-1));

	if (!alloc_cpumask_var(&mask, GFP_KERNEL))
		return 0;

	cpumask_and(mask, cpumask_of_node(node_dev->dev.id), cpu_online_mask);
	n = cpumap_print_to_pagebuf(list, buf, mask);
	free_cpumask_var(mask);

	return n;
}
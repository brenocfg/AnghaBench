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
struct rproc_mem_entry {int /*<<< orphan*/  node; } ;
struct rproc {int /*<<< orphan*/  carveouts; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rproc_add_carveout(struct rproc *rproc, struct rproc_mem_entry *mem)
{
	list_add_tail(&mem->node, &rproc->carveouts);
}
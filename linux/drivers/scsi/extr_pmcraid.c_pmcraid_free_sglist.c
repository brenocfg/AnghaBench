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
struct pmcraid_sglist {int /*<<< orphan*/  order; int /*<<< orphan*/  scatterlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pmcraid_sglist*) ; 
 int /*<<< orphan*/  sgl_free_order (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_free_sglist(struct pmcraid_sglist *sglist)
{
	sgl_free_order(sglist->scatterlist, sglist->order);
	kfree(sglist);
}
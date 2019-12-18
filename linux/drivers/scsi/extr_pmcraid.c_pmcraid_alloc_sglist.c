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
struct pmcraid_sglist {int order; int /*<<< orphan*/  num_sg; } ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int PMCRAID_MAX_IOADLS ; 
 int __GFP_ZERO ; 
 int get_order (int) ; 
 struct pmcraid_sglist* kzalloc (int,int) ; 
 int /*<<< orphan*/  sgl_alloc_order (int,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pmcraid_sglist *pmcraid_alloc_sglist(int buflen)
{
	struct pmcraid_sglist *sglist;
	int sg_size;
	int order;

	sg_size = buflen / (PMCRAID_MAX_IOADLS - 1);
	order = (sg_size > 0) ? get_order(sg_size) : 0;

	/* Allocate a scatter/gather list for the DMA */
	sglist = kzalloc(sizeof(struct pmcraid_sglist), GFP_KERNEL);
	if (sglist == NULL)
		return NULL;

	sglist->order = order;
	sgl_alloc_order(buflen, order, false,
			GFP_KERNEL | GFP_DMA | __GFP_ZERO, &sglist->num_sg);

	return sglist;
}
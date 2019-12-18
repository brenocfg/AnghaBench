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
struct ipr_sglist {int order; int /*<<< orphan*/  scatterlist; int /*<<< orphan*/  num_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPR_MAX_SGLIST ; 
 int get_order (int) ; 
 int /*<<< orphan*/  ipr_trace ; 
 int /*<<< orphan*/  kfree (struct ipr_sglist*) ; 
 struct ipr_sglist* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgl_alloc_order (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ipr_sglist *ipr_alloc_ucode_buffer(int buf_len)
{
	int sg_size, order;
	struct ipr_sglist *sglist;

	/* Get the minimum size per scatter/gather element */
	sg_size = buf_len / (IPR_MAX_SGLIST - 1);

	/* Get the actual size per element */
	order = get_order(sg_size);

	/* Allocate a scatter/gather list for the DMA */
	sglist = kzalloc(sizeof(struct ipr_sglist), GFP_KERNEL);
	if (sglist == NULL) {
		ipr_trace;
		return NULL;
	}
	sglist->order = order;
	sglist->scatterlist = sgl_alloc_order(buf_len, order, false, GFP_KERNEL,
					      &sglist->num_sg);
	if (!sglist->scatterlist) {
		kfree(sglist);
		return NULL;
	}

	return sglist;
}
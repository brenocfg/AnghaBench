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
struct scatterlist {unsigned int length; } ;

/* Variables and functions */
 int EINVAL ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

int spu_sg_at_offset(struct scatterlist *sg, unsigned int skip,
		     struct scatterlist **sge, unsigned int *sge_offset)
{
	/* byte index from start of sg to the end of the previous entry */
	unsigned int index = 0;
	/* byte index from start of sg to the end of the current entry */
	unsigned int next_index;

	next_index = sg->length;
	while (next_index <= skip) {
		sg = sg_next(sg);
		index = next_index;
		if (!sg)
			return -EINVAL;
		next_index += sg->length;
	}

	*sge_offset = skip - index;
	*sge = sg;
	return 0;
}
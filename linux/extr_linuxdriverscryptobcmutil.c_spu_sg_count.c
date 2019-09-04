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
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ spu_sg_at_offset (struct scatterlist*,unsigned int,struct scatterlist**,unsigned int*) ; 

int spu_sg_count(struct scatterlist *sg_list, unsigned int skip, int nbytes)
{
	struct scatterlist *sg;
	int sg_nents = 0;
	unsigned int offset;

	if (!sg_list)
		return 0;

	if (spu_sg_at_offset(sg_list, skip, &sg, &offset) < 0)
		return 0;

	while (sg && (nbytes > 0)) {
		sg_nents++;
		nbytes -= (sg->length - offset);
		offset = 0;
		sg = sg_next(sg);
	}
	return sg_nents;
}
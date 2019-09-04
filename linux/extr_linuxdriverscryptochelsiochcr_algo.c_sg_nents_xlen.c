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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int sg_nents_xlen(struct scatterlist *sg, unsigned int reqlen,
			 unsigned int entlen,
			 unsigned int skip)
{
	int nents = 0;
	unsigned int less;
	unsigned int skip_len = 0;

	while (sg && skip) {
		if (sg_dma_len(sg) <= skip) {
			skip -= sg_dma_len(sg);
			skip_len = 0;
			sg = sg_next(sg);
		} else {
			skip_len = skip;
			skip = 0;
		}
	}

	while (sg && reqlen) {
		less = min(reqlen, sg_dma_len(sg) - skip_len);
		nents += DIV_ROUND_UP(less, entlen);
		reqlen -= less;
		skip_len = 0;
		sg = sg_next(sg);
	}
	return nents;
}
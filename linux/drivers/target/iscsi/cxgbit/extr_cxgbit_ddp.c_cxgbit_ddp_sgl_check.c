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
struct scatterlist {unsigned int offset; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PAGE_SIZE ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int cxgbit_ddp_sgl_check(struct scatterlist *sg,
				unsigned int nents)
{
	unsigned int last_sgidx = nents - 1;
	unsigned int i;

	for (i = 0; i < nents; i++, sg = sg_next(sg)) {
		unsigned int len = sg->length + sg->offset;

		if ((sg->offset & 0x3) || (i && sg->offset) ||
		    ((i != last_sgidx) && (len != PAGE_SIZE))) {
			return -EINVAL;
		}
	}

	return 0;
}
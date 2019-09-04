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
struct scatterlist {int offset; int length; } ;

/* Variables and functions */
 int CACHE_LINE_MASK ; 

extern int bcm_sg_suitable_for_dma(struct scatterlist *sg_ptr, int sg_len)
{
	int i;

	for (i = 0; i < sg_len; i++) {
		if (sg_ptr[i].offset & CACHE_LINE_MASK ||
		    sg_ptr[i].length & CACHE_LINE_MASK)
			return 0;
	}

	return 1;
}
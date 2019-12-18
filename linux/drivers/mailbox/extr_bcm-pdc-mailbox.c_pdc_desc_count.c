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
typedef  int u32 ;
struct scatterlist {int length; } ;

/* Variables and functions */
 int PDC_DMA_BUF_MAX ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static u32 pdc_desc_count(struct scatterlist *sg)
{
	u32 cnt = 0;

	while (sg) {
		cnt += ((sg->length / PDC_DMA_BUF_MAX) + 1);
		sg = sg_next(sg);
	}
	return cnt;
}
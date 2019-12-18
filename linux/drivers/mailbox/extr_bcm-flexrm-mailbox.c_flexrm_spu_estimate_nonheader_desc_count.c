#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct scatterlist {unsigned int length; } ;
struct TYPE_2__ {struct scatterlist* dst; struct scatterlist* src; } ;
struct brcm_message {TYPE_1__ spu; } ;

/* Variables and functions */
 unsigned int UINT_MAX ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static u32 flexrm_spu_estimate_nonheader_desc_count(struct brcm_message *msg)
{
	u32 cnt = 0;
	unsigned int dst_target = 0;
	struct scatterlist *src_sg = msg->spu.src, *dst_sg = msg->spu.dst;

	while (src_sg || dst_sg) {
		if (src_sg) {
			cnt++;
			dst_target = src_sg->length;
			src_sg = sg_next(src_sg);
		} else
			dst_target = UINT_MAX;

		while (dst_target && dst_sg) {
			cnt++;
			if (dst_sg->length < dst_target)
				dst_target -= dst_sg->length;
			else
				dst_target = 0;
			dst_sg = sg_next(dst_sg);
		}
	}

	return cnt;
}
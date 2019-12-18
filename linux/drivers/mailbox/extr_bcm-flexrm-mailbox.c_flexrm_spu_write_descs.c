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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_2__ {struct scatterlist* dst; struct scatterlist* src; } ;
struct brcm_message {TYPE_1__ spu; } ;

/* Variables and functions */
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  flexrm_dst_desc (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  flexrm_enqueue_desc (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void**,scalar_t__*,void*,void*) ; 
 int /*<<< orphan*/  flexrm_flip_header_toggle (void*) ; 
 int /*<<< orphan*/  flexrm_mdst_desc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flexrm_msrc_desc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flexrm_null_desc (int) ; 
 int /*<<< orphan*/  flexrm_src_desc (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  flexrm_write_desc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void *flexrm_spu_write_descs(struct brcm_message *msg, u32 nhcnt,
				     u32 reqid, void *desc_ptr, u32 toggle,
				     void *start_desc, void *end_desc)
{
	u64 d;
	u32 nhpos = 0;
	void *orig_desc_ptr = desc_ptr;
	unsigned int dst_target = 0;
	struct scatterlist *src_sg = msg->spu.src, *dst_sg = msg->spu.dst;

	while (src_sg || dst_sg) {
		if (src_sg) {
			if (sg_dma_len(src_sg) & 0xf)
				d = flexrm_src_desc(sg_dma_address(src_sg),
						     sg_dma_len(src_sg));
			else
				d = flexrm_msrc_desc(sg_dma_address(src_sg),
						      sg_dma_len(src_sg)/16);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
			dst_target = sg_dma_len(src_sg);
			src_sg = sg_next(src_sg);
		} else
			dst_target = UINT_MAX;

		while (dst_target && dst_sg) {
			if (sg_dma_len(dst_sg) & 0xf)
				d = flexrm_dst_desc(sg_dma_address(dst_sg),
						     sg_dma_len(dst_sg));
			else
				d = flexrm_mdst_desc(sg_dma_address(dst_sg),
						      sg_dma_len(dst_sg)/16);
			flexrm_enqueue_desc(nhpos, nhcnt, reqid,
					     d, &desc_ptr, &toggle,
					     start_desc, end_desc);
			nhpos++;
			if (sg_dma_len(dst_sg) < dst_target)
				dst_target -= sg_dma_len(dst_sg);
			else
				dst_target = 0;
			dst_sg = sg_next(dst_sg);
		}
	}

	/* Null descriptor with invalid toggle bit */
	flexrm_write_desc(desc_ptr, flexrm_null_desc(!toggle));

	/* Ensure that descriptors have been written to memory */
	wmb();

	/* Flip toggle bit in header */
	flexrm_flip_header_toggle(orig_desc_ptr);

	return desc_ptr;
}
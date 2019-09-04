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
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int cc_render_buff_to_mlli (struct device*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__**) ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int cc_render_sg_to_mlli(struct device *dev, struct scatterlist *sgl,
				u32 sgl_data_len, u32 sgl_offset,
				u32 *curr_nents, u32 **mlli_entry_pp)
{
	struct scatterlist *curr_sgl = sgl;
	u32 *mlli_entry_p = *mlli_entry_pp;
	s32 rc = 0;

	for ( ; (curr_sgl && sgl_data_len);
	      curr_sgl = sg_next(curr_sgl)) {
		u32 entry_data_len =
			(sgl_data_len > sg_dma_len(curr_sgl) - sgl_offset) ?
				sg_dma_len(curr_sgl) - sgl_offset :
				sgl_data_len;
		sgl_data_len -= entry_data_len;
		rc = cc_render_buff_to_mlli(dev, sg_dma_address(curr_sgl) +
					    sgl_offset, entry_data_len,
					    curr_nents, &mlli_entry_p);
		if (rc)
			return rc;

		sgl_offset = 0;
	}
	*mlli_entry_pp = mlli_entry_p;
	return 0;
}
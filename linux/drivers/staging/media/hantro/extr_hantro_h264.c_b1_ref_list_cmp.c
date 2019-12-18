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
typedef  size_t u8 ;
struct v4l2_h264_dpb_entry {int flags; int pic_num; } ;
struct hantro_h264_reflist_builder {scalar_t__* pocs; scalar_t__ curpoc; struct v4l2_h264_dpb_entry* dpb; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int POC_CMP (scalar_t__,scalar_t__) ; 
 int V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM ; 

__attribute__((used)) static int b1_ref_list_cmp(const void *ptra, const void *ptrb, const void *data)
{
	const struct hantro_h264_reflist_builder *builder = data;
	const struct v4l2_h264_dpb_entry *a, *b;
	s32 poca, pocb;
	u8 idxa, idxb;

	idxa = *((u8 *)ptra);
	idxb = *((u8 *)ptrb);
	a = &builder->dpb[idxa];
	b = &builder->dpb[idxb];

	if ((a->flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM) !=
	    (b->flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM)) {
		/* Short term pics firt. */
		if (!(a->flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM))
			return -1;
		else
			return 1;
	}

	/* Long term pics in ascending pic num order. */
	if (a->flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM)
		return a->pic_num - b->pic_num;

	poca = builder->pocs[idxa];
	pocb = builder->pocs[idxb];

	/*
	 * Short term pics with POC > cur POC first in POC ascending order
	 * followed by short term pics with POC > cur POC in POC descending
	 * order.
	 */
	if ((poca < builder->curpoc) != (pocb < builder->curpoc))
		return POC_CMP(pocb, poca);
	else if (poca < builder->curpoc)
		return POC_CMP(pocb, poca);

	return POC_CMP(poca, pocb);
}
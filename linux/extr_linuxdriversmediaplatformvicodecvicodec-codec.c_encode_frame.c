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
struct raw_frame {unsigned int height; unsigned int width; int chroma_step; int /*<<< orphan*/  cr; int /*<<< orphan*/  cb; int /*<<< orphan*/  luma; } ;
struct cframe {int size; int /*<<< orphan*/ * rlc_data; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int CB_UNENCODED ; 
 int CR_UNENCODED ; 
 int FRAME_UNENCODED ; 
 int LUMA_UNENCODED ; 
 int encode_plane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,struct cframe*,int,int,int,int,int) ; 

u32 encode_frame(struct raw_frame *frm, struct raw_frame *ref_frm,
		 struct cframe *cf, bool is_intra, bool next_is_intra)
{
	unsigned int size = frm->height * frm->width;
	__be16 *rlco = cf->rlc_data;
	__be16 *rlco_max;
	u32 encoding;

	rlco_max = rlco + size / 2 - 256;
	encoding = encode_plane(frm->luma, ref_frm->luma, &rlco, rlco_max, cf,
				  frm->height, frm->width,
				  1, is_intra, next_is_intra);
	if (encoding & FRAME_UNENCODED)
		encoding |= LUMA_UNENCODED;
	encoding &= ~FRAME_UNENCODED;
	rlco_max = rlco + size / 8 - 256;
	encoding |= encode_plane(frm->cb, ref_frm->cb, &rlco, rlco_max, cf,
				   frm->height / 2, frm->width / 2,
				   frm->chroma_step, is_intra, next_is_intra);
	if (encoding & FRAME_UNENCODED)
		encoding |= CB_UNENCODED;
	encoding &= ~FRAME_UNENCODED;
	rlco_max = rlco + size / 8 - 256;
	encoding |= encode_plane(frm->cr, ref_frm->cr, &rlco, rlco_max, cf,
				   frm->height / 2, frm->width / 2,
				   frm->chroma_step, is_intra, next_is_intra);
	if (encoding & FRAME_UNENCODED)
		encoding |= CR_UNENCODED;
	encoding &= ~FRAME_UNENCODED;
	cf->size = (rlco - cf->rlc_data) * sizeof(*rlco);
	return encoding;
}
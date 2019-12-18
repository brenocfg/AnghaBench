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
struct mcif_wb_frame_dump_info {int format; unsigned int width; unsigned int height; unsigned int luma_pitch; unsigned int chroma_pitch; unsigned int size; } ;
struct mcif_wb {int dummy; } ;
struct mcif_buf_params {unsigned int luma_pitch; unsigned int chroma_pitch; } ;
struct dcn20_mmhubbub {int dummy; } ;
typedef  enum dwb_scaler_mode { ____Placeholder_dwb_scaler_mode } dwb_scaler_mode ;

/* Variables and functions */
 int /*<<< orphan*/  MCIF_WB_BUFMGR_SW_CONTROL ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_SW_LOCK ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_mmhubbub* TO_DCN20_MMHUBBUB (struct mcif_wb*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 

void mcifwb2_dump_frame(struct mcif_wb *mcif_wb,
		struct mcif_buf_params *mcif_params,
		enum dwb_scaler_mode out_format,
		unsigned int dest_width,
		unsigned int dest_height,
		struct mcif_wb_frame_dump_info *dump_info,
		unsigned char *luma_buffer,
		unsigned char *chroma_buffer,
		unsigned char *dest_luma_buffer,
		unsigned char *dest_chroma_buffer)
{
	struct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_LOCK, 0xf);

	memcpy(dest_luma_buffer,   luma_buffer,   mcif_params->luma_pitch * dest_height);
	memcpy(dest_chroma_buffer, chroma_buffer, mcif_params->chroma_pitch * dest_height / 2);

	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_LOCK, 0x0);

	dump_info->format	= out_format;
	dump_info->width	= dest_width;
	dump_info->height	= dest_height;
	dump_info->luma_pitch	= mcif_params->luma_pitch;
	dump_info->chroma_pitch	= mcif_params->chroma_pitch;
	dump_info->size		= dest_height * (mcif_params->luma_pitch + mcif_params->chroma_pitch);
}
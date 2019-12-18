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
struct mcif_wb {int dummy; } ;
struct mcif_buf_params {int swlock; int luma_pitch; int chroma_pitch; int warmup_pitch; int /*<<< orphan*/ * chroma_address; int /*<<< orphan*/ * luma_address; } ;
struct dcn20_mmhubbub {int dummy; } ;

/* Variables and functions */
 int MCIF_ADDR (int /*<<< orphan*/ ) ; 
 int MCIF_ADDR_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_SW_CONTROL ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_SW_LOCK ; 
 int /*<<< orphan*/  MCIF_WB_BUF_1_ADDR_C ; 
 int /*<<< orphan*/  MCIF_WB_BUF_1_ADDR_C_HIGH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_1_ADDR_C_OFFSET ; 
 int /*<<< orphan*/  MCIF_WB_BUF_1_ADDR_Y ; 
 int /*<<< orphan*/  MCIF_WB_BUF_1_ADDR_Y_HIGH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_1_ADDR_Y_OFFSET ; 
 int /*<<< orphan*/  MCIF_WB_BUF_2_ADDR_C ; 
 int /*<<< orphan*/  MCIF_WB_BUF_2_ADDR_C_HIGH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_2_ADDR_C_OFFSET ; 
 int /*<<< orphan*/  MCIF_WB_BUF_2_ADDR_Y ; 
 int /*<<< orphan*/  MCIF_WB_BUF_2_ADDR_Y_HIGH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_2_ADDR_Y_OFFSET ; 
 int /*<<< orphan*/  MCIF_WB_BUF_3_ADDR_C ; 
 int /*<<< orphan*/  MCIF_WB_BUF_3_ADDR_C_HIGH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_3_ADDR_C_OFFSET ; 
 int /*<<< orphan*/  MCIF_WB_BUF_3_ADDR_Y ; 
 int /*<<< orphan*/  MCIF_WB_BUF_3_ADDR_Y_HIGH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_3_ADDR_Y_OFFSET ; 
 int /*<<< orphan*/  MCIF_WB_BUF_4_ADDR_C ; 
 int /*<<< orphan*/  MCIF_WB_BUF_4_ADDR_C_HIGH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_4_ADDR_C_OFFSET ; 
 int /*<<< orphan*/  MCIF_WB_BUF_4_ADDR_Y ; 
 int /*<<< orphan*/  MCIF_WB_BUF_4_ADDR_Y_HIGH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_4_ADDR_Y_OFFSET ; 
 int /*<<< orphan*/  MCIF_WB_BUF_ADDR_FENCE_EN ; 
 int /*<<< orphan*/  MCIF_WB_BUF_CHROMA_PITCH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_CHROMA_SIZE ; 
 int /*<<< orphan*/  MCIF_WB_BUF_LUMA_PITCH ; 
 int /*<<< orphan*/  MCIF_WB_BUF_LUMA_SIZE ; 
 int /*<<< orphan*/  MCIF_WB_BUF_PITCH ; 
 int /*<<< orphan*/  MCIF_WB_PITCH_SIZE_WARMUP ; 
 int /*<<< orphan*/  MCIF_WB_WARM_UP_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dcn20_mmhubbub* TO_DCN20_MMHUBBUB (struct mcif_wb*) ; 

__attribute__((used)) static void mmhubbub2_config_mcif_buf(struct mcif_wb *mcif_wb,
		struct mcif_buf_params *params,
		unsigned int dest_height)
{
	struct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	/* sw lock buffer0~buffer3, default is 0 */
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUFMGR_SW_LOCK, params->swlock);

	/* buffer address for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_Y, MCIF_WB_BUF_1_ADDR_Y, MCIF_ADDR(params->luma_address[0]));
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_Y_HIGH, MCIF_WB_BUF_1_ADDR_Y_HIGH, MCIF_ADDR_HIGH(params->luma_address[0]));
	/* right eye sub-buffer address offset for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_Y_OFFSET, MCIF_WB_BUF_1_ADDR_Y_OFFSET, 0);

	/* buffer address for Chroma in planar mode (unused in packing mode) */
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_C, MCIF_WB_BUF_1_ADDR_C, MCIF_ADDR(params->chroma_address[0]));
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_C_HIGH, MCIF_WB_BUF_1_ADDR_C_HIGH, MCIF_ADDR_HIGH(params->chroma_address[0]));
	/* right eye offset for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_1_ADDR_C_OFFSET, MCIF_WB_BUF_1_ADDR_C_OFFSET, 0);

	/* buffer address for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_Y, MCIF_WB_BUF_2_ADDR_Y, MCIF_ADDR(params->luma_address[1]));
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_Y_HIGH, MCIF_WB_BUF_2_ADDR_Y_HIGH, MCIF_ADDR_HIGH(params->luma_address[1]));
	/* right eye sub-buffer address offset for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_Y_OFFSET, MCIF_WB_BUF_2_ADDR_Y_OFFSET, 0);

	/* buffer address for Chroma in planar mode (unused in packing mode) */
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_C, MCIF_WB_BUF_2_ADDR_C, MCIF_ADDR(params->chroma_address[1]));
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_C_HIGH, MCIF_WB_BUF_2_ADDR_C_HIGH, MCIF_ADDR_HIGH(params->chroma_address[1]));
	/* right eye offset for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_2_ADDR_C_OFFSET, MCIF_WB_BUF_2_ADDR_C_OFFSET, 0);

	/* buffer address for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_Y, MCIF_WB_BUF_3_ADDR_Y, MCIF_ADDR(params->luma_address[2]));
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_Y_HIGH, MCIF_WB_BUF_3_ADDR_Y_HIGH, MCIF_ADDR_HIGH(params->luma_address[2]));
	/* right eye sub-buffer address offset for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_Y_OFFSET, MCIF_WB_BUF_3_ADDR_Y_OFFSET, 0);

	/* buffer address for Chroma in planar mode (unused in packing mode) */
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_C, MCIF_WB_BUF_3_ADDR_C, MCIF_ADDR(params->chroma_address[2]));
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_C_HIGH, MCIF_WB_BUF_3_ADDR_C_HIGH, MCIF_ADDR_HIGH(params->chroma_address[2]));
	/* right eye offset for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_3_ADDR_C_OFFSET, MCIF_WB_BUF_3_ADDR_C_OFFSET, 0);

	/* buffer address for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_Y, MCIF_WB_BUF_4_ADDR_Y, MCIF_ADDR(params->luma_address[3]));
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_Y_HIGH, MCIF_WB_BUF_4_ADDR_Y_HIGH, MCIF_ADDR_HIGH(params->luma_address[3]));
	/* right eye sub-buffer address offset for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_Y_OFFSET, MCIF_WB_BUF_4_ADDR_Y_OFFSET, 0);

	/* buffer address for Chroma in planar mode (unused in packing mode) */
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_C, MCIF_WB_BUF_4_ADDR_C, MCIF_ADDR(params->chroma_address[3]));
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_C_HIGH, MCIF_WB_BUF_4_ADDR_C_HIGH, MCIF_ADDR_HIGH(params->chroma_address[3]));
	/* right eye offset for packing mode or Luma in planar mode */
	REG_UPDATE(MCIF_WB_BUF_4_ADDR_C_OFFSET, MCIF_WB_BUF_4_ADDR_C_OFFSET, 0);

	/* setup luma & chroma size
	 * should be enough to contain a whole frame Luma data,
	 * the programmed value is frame buffer size [27:8], 256-byte aligned
	 */
	REG_UPDATE(MCIF_WB_BUF_LUMA_SIZE, MCIF_WB_BUF_LUMA_SIZE, (params->luma_pitch>>8) * dest_height);
	REG_UPDATE(MCIF_WB_BUF_CHROMA_SIZE, MCIF_WB_BUF_CHROMA_SIZE, (params->chroma_pitch>>8) * dest_height);

	/* enable address fence */
	REG_UPDATE(MCIF_WB_BUFMGR_SW_CONTROL, MCIF_WB_BUF_ADDR_FENCE_EN, 1);

	/* setup pitch, the programmed value is [15:8], 256B align */
	REG_UPDATE_2(MCIF_WB_BUF_PITCH, MCIF_WB_BUF_LUMA_PITCH, params->luma_pitch >> 8,
			MCIF_WB_BUF_CHROMA_PITCH, params->chroma_pitch >> 8);

	/* Set pitch for MC cache warm up mode */
	/* Pitch is 256 bytes aligned. The default pitch is 4K */
	/* default is 0x10 */
	REG_UPDATE(MCIF_WB_WARM_UP_CNTL, MCIF_WB_PITCH_SIZE_WARMUP, params->warmup_pitch);
}
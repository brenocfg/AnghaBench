#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct vb2_buffer {int dummy; } ;
struct v4l2_h264_dpb_entry {int flags; int /*<<< orphan*/  frame_num; int /*<<< orphan*/  pic_num; } ;
struct hantro_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * p; int /*<<< orphan*/ * b1; int /*<<< orphan*/ * b0; } ;
struct TYPE_4__ {TYPE_1__ reflists; struct v4l2_h264_dpb_entry* dpb; } ;
struct hantro_ctx {TYPE_2__ h264_dec; struct hantro_dev* dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  G1_REG_ADDR_REF (int) ; 
 int /*<<< orphan*/  G1_REG_BD_P_REF_PIC ; 
 int G1_REG_BD_P_REF_PIC_BINIT_RLIST_B15 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_P_REF_PIC_BINIT_RLIST_F15 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_P_REF_PIC_PINIT_RLIST_F0 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_P_REF_PIC_PINIT_RLIST_F1 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_P_REF_PIC_PINIT_RLIST_F2 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_P_REF_PIC_PINIT_RLIST_F3 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  G1_REG_BD_REF_PIC (int /*<<< orphan*/ ) ; 
 int G1_REG_BD_REF_PIC_BINIT_RLIST_B0 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_REF_PIC_BINIT_RLIST_B1 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_REF_PIC_BINIT_RLIST_B2 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_REF_PIC_BINIT_RLIST_F0 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_REF_PIC_BINIT_RLIST_F1 (int /*<<< orphan*/  const) ; 
 int G1_REG_BD_REF_PIC_BINIT_RLIST_F2 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  G1_REG_FWD_PIC (int /*<<< orphan*/ ) ; 
 int G1_REG_FWD_PIC_PINIT_RLIST_F0 (int /*<<< orphan*/  const) ; 
 int G1_REG_FWD_PIC_PINIT_RLIST_F1 (int /*<<< orphan*/  const) ; 
 int G1_REG_FWD_PIC_PINIT_RLIST_F2 (int /*<<< orphan*/  const) ; 
 int G1_REG_FWD_PIC_PINIT_RLIST_F3 (int /*<<< orphan*/  const) ; 
 int G1_REG_FWD_PIC_PINIT_RLIST_F4 (int /*<<< orphan*/  const) ; 
 int G1_REG_FWD_PIC_PINIT_RLIST_F5 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  G1_REG_LT_REF ; 
 int /*<<< orphan*/  G1_REG_REF_PIC (int) ; 
 int G1_REG_REF_PIC_REFER0_NBR (int /*<<< orphan*/ ) ; 
 int G1_REG_REF_PIC_REFER1_NBR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G1_REG_VALID_REF ; 
 int HANTRO_H264_DPB_SIZE ; 
 int V4L2_H264_DPB_ENTRY_FLAG_ACTIVE ; 
 int V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM ; 
 struct vb2_buffer* hantro_h264_get_ref_buf (struct hantro_ctx*,int) ; 
 int vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_ref(struct hantro_ctx *ctx)
{
	struct v4l2_h264_dpb_entry *dpb = ctx->h264_dec.dpb;
	const u8 *b0_reflist, *b1_reflist, *p_reflist;
	struct hantro_dev *vpu = ctx->dev;
	u32 dpb_longterm = 0;
	u32 dpb_valid = 0;
	int reg_num;
	u32 reg;
	int i;

	/*
	 * Set up bit maps of valid and long term DPBs.
	 * NOTE: The bits are reversed, i.e. MSb is DPB 0.
	 */
	for (i = 0; i < HANTRO_H264_DPB_SIZE; ++i) {
		if (dpb[i].flags & V4L2_H264_DPB_ENTRY_FLAG_ACTIVE)
			dpb_valid |= BIT(HANTRO_H264_DPB_SIZE - 1 - i);

		if (dpb[i].flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM)
			dpb_longterm |= BIT(HANTRO_H264_DPB_SIZE - 1 - i);
	}
	vdpu_write_relaxed(vpu, dpb_valid << 16, G1_REG_VALID_REF);
	vdpu_write_relaxed(vpu, dpb_longterm << 16, G1_REG_LT_REF);

	/*
	 * Set up reference frame picture numbers.
	 *
	 * Each G1_REG_REF_PIC(x) register contains numbers of two
	 * subsequential reference pictures.
	 */
	for (i = 0; i < HANTRO_H264_DPB_SIZE; i += 2) {
		reg = 0;
		if (dpb[i].flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM)
			reg |= G1_REG_REF_PIC_REFER0_NBR(dpb[i].pic_num);
		else
			reg |= G1_REG_REF_PIC_REFER0_NBR(dpb[i].frame_num);

		if (dpb[i + 1].flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM)
			reg |= G1_REG_REF_PIC_REFER1_NBR(dpb[i + 1].pic_num);
		else
			reg |= G1_REG_REF_PIC_REFER1_NBR(dpb[i + 1].frame_num);

		vdpu_write_relaxed(vpu, reg, G1_REG_REF_PIC(i / 2));
	}

	b0_reflist = ctx->h264_dec.reflists.b0;
	b1_reflist = ctx->h264_dec.reflists.b1;
	p_reflist = ctx->h264_dec.reflists.p;

	/*
	 * Each G1_REG_BD_REF_PIC(x) register contains three entries
	 * of each forward and backward picture list.
	 */
	reg_num = 0;
	for (i = 0; i < 15; i += 3) {
		reg = G1_REG_BD_REF_PIC_BINIT_RLIST_F0(b0_reflist[i]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_F1(b0_reflist[i + 1]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_F2(b0_reflist[i + 2]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_B0(b1_reflist[i]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_B1(b1_reflist[i + 1]) |
		      G1_REG_BD_REF_PIC_BINIT_RLIST_B2(b1_reflist[i + 2]);
		vdpu_write_relaxed(vpu, reg, G1_REG_BD_REF_PIC(reg_num++));
	}

	/*
	 * G1_REG_BD_P_REF_PIC register contains last entries (index 15)
	 * of forward and backward reference picture lists and first 4 entries
	 * of P forward picture list.
	 */
	reg = G1_REG_BD_P_REF_PIC_BINIT_RLIST_F15(b0_reflist[15]) |
	      G1_REG_BD_P_REF_PIC_BINIT_RLIST_B15(b1_reflist[15]) |
	      G1_REG_BD_P_REF_PIC_PINIT_RLIST_F0(p_reflist[0]) |
	      G1_REG_BD_P_REF_PIC_PINIT_RLIST_F1(p_reflist[1]) |
	      G1_REG_BD_P_REF_PIC_PINIT_RLIST_F2(p_reflist[2]) |
	      G1_REG_BD_P_REF_PIC_PINIT_RLIST_F3(p_reflist[3]);
	vdpu_write_relaxed(vpu, reg, G1_REG_BD_P_REF_PIC);

	/*
	 * Each G1_REG_FWD_PIC(x) register contains six consecutive
	 * entries of P forward picture list, starting from index 4.
	 */
	reg_num = 0;
	for (i = 4; i < HANTRO_H264_DPB_SIZE; i += 6) {
		reg = G1_REG_FWD_PIC_PINIT_RLIST_F0(p_reflist[i]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F1(p_reflist[i + 1]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F2(p_reflist[i + 2]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F3(p_reflist[i + 3]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F4(p_reflist[i + 4]) |
		      G1_REG_FWD_PIC_PINIT_RLIST_F5(p_reflist[i + 5]);
		vdpu_write_relaxed(vpu, reg, G1_REG_FWD_PIC(reg_num++));
	}

	/* Set up addresses of DPB buffers. */
	for (i = 0; i < HANTRO_H264_DPB_SIZE; i++) {
		struct vb2_buffer *buf =  hantro_h264_get_ref_buf(ctx, i);

		vdpu_write_relaxed(vpu, vb2_dma_contig_plane_dma_addr(buf, 0),
				   G1_REG_ADDR_REF(i));
	}
}
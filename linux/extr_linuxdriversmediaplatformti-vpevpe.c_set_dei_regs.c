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
typedef  unsigned int u32 ;
struct TYPE_4__ {unsigned int height; unsigned int width; } ;
struct vpe_q_data {int flags; TYPE_2__ c_rect; } ;
struct vpe_mmr_adb {unsigned int* dei_regs; } ;
struct TYPE_3__ {struct vpe_mmr_adb* addr; } ;
struct vpe_ctx {int load_mmrs; int /*<<< orphan*/  deinterlacing; struct vpe_q_data* q_data; TYPE_1__ mmr_adb; } ;

/* Variables and functions */
 size_t Q_DATA_SRC ; 
 int Q_IS_INTERLACED ; 
 unsigned int VPE_DEI_FIELD_FLUSH ; 
 unsigned int VPE_DEI_HEIGHT_SHIFT ; 
 unsigned int VPE_DEI_INTERLACE_BYPASS ; 
 unsigned int VPE_DEI_WIDTH_SHIFT ; 

__attribute__((used)) static void set_dei_regs(struct vpe_ctx *ctx)
{
	struct vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	struct vpe_q_data *s_q_data = &ctx->q_data[Q_DATA_SRC];
	unsigned int src_h = s_q_data->c_rect.height;
	unsigned int src_w = s_q_data->c_rect.width;
	u32 *dei_mmr0 = &mmr_adb->dei_regs[0];
	bool deinterlace = true;
	u32 val = 0;

	/*
	 * according to TRM, we should set DEI in progressive bypass mode when
	 * the input content is progressive, however, DEI is bypassed correctly
	 * for both progressive and interlace content in interlace bypass mode.
	 * It has been recommended not to use progressive bypass mode.
	 */
	if (!(s_q_data->flags & Q_IS_INTERLACED) || !ctx->deinterlacing) {
		deinterlace = false;
		val = VPE_DEI_INTERLACE_BYPASS;
	}

	src_h = deinterlace ? src_h * 2 : src_h;

	val |= (src_h << VPE_DEI_HEIGHT_SHIFT) |
		(src_w << VPE_DEI_WIDTH_SHIFT) |
		VPE_DEI_FIELD_FLUSH;

	*dei_mmr0 = val;

	ctx->load_mmrs = true;
}
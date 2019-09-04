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
struct TYPE_2__ {int /*<<< orphan*/ * plane_addr; } ;
struct dpu_hw_pipe_cfg {TYPE_1__ layout; } ;
struct dpu_hw_pipe {int /*<<< orphan*/  hw; } ;
typedef  enum dpu_sspp_multirect_index { ____Placeholder_dpu_sspp_multirect_index } dpu_sspp_multirect_index ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int DPU_SSPP_RECT_0 ; 
 int DPU_SSPP_RECT_SOLO ; 
 int /*<<< orphan*/  DPU_SSPP_SRC ; 
 scalar_t__ SSPP_SRC0_ADDR ; 
 scalar_t__ SSPP_SRC1_ADDR ; 
 scalar_t__ SSPP_SRC2_ADDR ; 
 scalar_t__ SSPP_SRC3_ADDR ; 
 scalar_t__ _sspp_subblk_offset (struct dpu_hw_pipe*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void dpu_hw_sspp_setup_sourceaddress(struct dpu_hw_pipe *ctx,
		struct dpu_hw_pipe_cfg *cfg,
		enum dpu_sspp_multirect_index rect_mode)
{
	int i;
	u32 idx;

	if (_sspp_subblk_offset(ctx, DPU_SSPP_SRC, &idx))
		return;

	if (rect_mode == DPU_SSPP_RECT_SOLO) {
		for (i = 0; i < ARRAY_SIZE(cfg->layout.plane_addr); i++)
			DPU_REG_WRITE(&ctx->hw, SSPP_SRC0_ADDR + idx + i * 0x4,
					cfg->layout.plane_addr[i]);
	} else if (rect_mode == DPU_SSPP_RECT_0) {
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC0_ADDR + idx,
				cfg->layout.plane_addr[0]);
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC2_ADDR + idx,
				cfg->layout.plane_addr[2]);
	} else {
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC1_ADDR + idx,
				cfg->layout.plane_addr[0]);
		DPU_REG_WRITE(&ctx->hw, SSPP_SRC3_ADDR + idx,
				cfg->layout.plane_addr[2]);
	}
}
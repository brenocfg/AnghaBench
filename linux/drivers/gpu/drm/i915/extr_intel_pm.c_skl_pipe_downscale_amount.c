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
typedef  int /*<<< orphan*/  uint_fixed_16_16_t ;
typedef  int u32 ;
struct TYPE_3__ {int size; scalar_t__ enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable; } ;
struct intel_crtc_state {int pipe_src_w; int pipe_src_h; TYPE_1__ pch_pfit; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  div_fixed16 (int,int) ; 
 int /*<<< orphan*/  max_fixed16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_fixed16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32_to_fixed16 (int) ; 

__attribute__((used)) static uint_fixed_16_16_t
skl_pipe_downscale_amount(const struct intel_crtc_state *crtc_state)
{
	uint_fixed_16_16_t pipe_downscale = u32_to_fixed16(1);

	if (!crtc_state->base.enable)
		return pipe_downscale;

	if (crtc_state->pch_pfit.enabled) {
		u32 src_w, src_h, dst_w, dst_h;
		u32 pfit_size = crtc_state->pch_pfit.size;
		uint_fixed_16_16_t fp_w_ratio, fp_h_ratio;
		uint_fixed_16_16_t downscale_h, downscale_w;

		src_w = crtc_state->pipe_src_w;
		src_h = crtc_state->pipe_src_h;
		dst_w = pfit_size >> 16;
		dst_h = pfit_size & 0xffff;

		if (!dst_w || !dst_h)
			return pipe_downscale;

		fp_w_ratio = div_fixed16(src_w, dst_w);
		fp_h_ratio = div_fixed16(src_h, dst_h);
		downscale_w = max_fixed16(fp_w_ratio, u32_to_fixed16(1));
		downscale_h = max_fixed16(fp_h_ratio, u32_to_fixed16(1));

		pipe_downscale = mul_fixed16(downscale_w, downscale_h);
	}

	return pipe_downscale;
}
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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_pending_flush ) (struct dpu_hw_ctl*) ;int /*<<< orphan*/  (* trigger_flush ) (struct dpu_hw_ctl*) ;int /*<<< orphan*/  (* update_pending_flush ) (struct dpu_hw_ctl*,int /*<<< orphan*/ ) ;} ;
struct dpu_hw_ctl {int /*<<< orphan*/  idx; TYPE_1__ ops; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  intf_idx; struct dpu_hw_ctl* hw_ctl; int /*<<< orphan*/  hw_pp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DRMID (struct drm_encoder*) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int dpu_encoder_phys_inc_pending (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  stub1 (struct dpu_hw_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dpu_hw_ctl*) ; 
 int /*<<< orphan*/  stub3 (struct dpu_hw_ctl*) ; 
 int /*<<< orphan*/  trace_dpu_enc_trigger_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dpu_encoder_trigger_flush(struct drm_encoder *drm_enc,
		struct dpu_encoder_phys *phys, uint32_t extra_flush_bits)
{
	struct dpu_hw_ctl *ctl;
	int pending_kickoff_cnt;
	u32 ret = UINT_MAX;

	if (!phys->hw_pp) {
		DPU_ERROR("invalid pingpong hw\n");
		return;
	}

	ctl = phys->hw_ctl;
	if (!ctl || !ctl->ops.trigger_flush) {
		DPU_ERROR("missing trigger cb\n");
		return;
	}

	pending_kickoff_cnt = dpu_encoder_phys_inc_pending(phys);

	if (extra_flush_bits && ctl->ops.update_pending_flush)
		ctl->ops.update_pending_flush(ctl, extra_flush_bits);

	ctl->ops.trigger_flush(ctl);

	if (ctl->ops.get_pending_flush)
		ret = ctl->ops.get_pending_flush(ctl);

	trace_dpu_enc_trigger_flush(DRMID(drm_enc), phys->intf_idx,
				    pending_kickoff_cnt, ctl->idx,
				    extra_flush_bits, ret);
}
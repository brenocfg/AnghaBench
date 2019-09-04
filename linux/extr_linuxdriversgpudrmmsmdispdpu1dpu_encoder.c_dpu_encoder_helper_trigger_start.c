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
struct TYPE_2__ {int /*<<< orphan*/  (* trigger_start ) (struct dpu_hw_ctl*) ;} ;
struct dpu_hw_ctl {int /*<<< orphan*/  idx; TYPE_1__ ops; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  parent; struct dpu_hw_ctl* hw_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dpu_hw_ctl*) ; 
 int /*<<< orphan*/  trace_dpu_enc_trigger_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dpu_encoder_helper_trigger_start(struct dpu_encoder_phys *phys_enc)
{
	struct dpu_hw_ctl *ctl;

	if (!phys_enc) {
		DPU_ERROR("invalid encoder\n");
		return;
	}

	ctl = phys_enc->hw_ctl;
	if (ctl && ctl->ops.trigger_start) {
		ctl->ops.trigger_start(ctl);
		trace_dpu_enc_trigger_start(DRMID(phys_enc->parent), ctl->idx);
	}
}
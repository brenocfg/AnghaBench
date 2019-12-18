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
struct dpu_encoder_phys_cmd {int dummy; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  vblank_refcount; TYPE_1__* hw_pp; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTR_IDX_CTL_START ; 
 int /*<<< orphan*/  INTR_IDX_PINGPONG ; 
 int /*<<< orphan*/  INTR_IDX_UNDERRUN ; 
 scalar_t__ PINGPONG_0 ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_encoder_helper_register_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_encoder_helper_unregister_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_control_vblank_irq (struct dpu_encoder_phys*,int) ; 
 scalar_t__ dpu_encoder_phys_cmd_is_master (struct dpu_encoder_phys*) ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 
 int /*<<< orphan*/  trace_dpu_enc_phys_cmd_irq_ctrl (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_irq_control(struct dpu_encoder_phys *phys_enc,
		bool enable)
{
	struct dpu_encoder_phys_cmd *cmd_enc;

	if (!phys_enc)
		return;

	cmd_enc = to_dpu_encoder_phys_cmd(phys_enc);

	trace_dpu_enc_phys_cmd_irq_ctrl(DRMID(phys_enc->parent),
			phys_enc->hw_pp->idx - PINGPONG_0,
			enable, atomic_read(&phys_enc->vblank_refcount));

	if (enable) {
		dpu_encoder_helper_register_irq(phys_enc, INTR_IDX_PINGPONG);
		dpu_encoder_helper_register_irq(phys_enc, INTR_IDX_UNDERRUN);
		dpu_encoder_phys_cmd_control_vblank_irq(phys_enc, true);

		if (dpu_encoder_phys_cmd_is_master(phys_enc))
			dpu_encoder_helper_register_irq(phys_enc,
					INTR_IDX_CTL_START);
	} else {
		if (dpu_encoder_phys_cmd_is_master(phys_enc))
			dpu_encoder_helper_unregister_irq(phys_enc,
					INTR_IDX_CTL_START);

		dpu_encoder_helper_unregister_irq(phys_enc, INTR_IDX_UNDERRUN);
		dpu_encoder_phys_cmd_control_vblank_irq(phys_enc, false);
		dpu_encoder_helper_unregister_irq(phys_enc, INTR_IDX_PINGPONG);
	}
}
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
struct dpu_encoder_phys {int /*<<< orphan*/  vblank_refcount; TYPE_1__* hw_intf; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 scalar_t__ INTF_0 ; 
 int /*<<< orphan*/  INTR_IDX_UNDERRUN ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_encoder_helper_register_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_encoder_helper_unregister_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int dpu_encoder_phys_vid_control_vblank_irq (struct dpu_encoder_phys*,int) ; 
 int /*<<< orphan*/  trace_dpu_enc_phys_vid_irq_ctrl (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpu_encoder_phys_vid_irq_control(struct dpu_encoder_phys *phys_enc,
		bool enable)
{
	int ret;

	if (!phys_enc)
		return;

	trace_dpu_enc_phys_vid_irq_ctrl(DRMID(phys_enc->parent),
			    phys_enc->hw_intf->idx - INTF_0,
			    enable,
			    atomic_read(&phys_enc->vblank_refcount));

	if (enable) {
		ret = dpu_encoder_phys_vid_control_vblank_irq(phys_enc, true);
		if (ret)
			return;

		dpu_encoder_helper_register_irq(phys_enc, INTR_IDX_UNDERRUN);
	} else {
		dpu_encoder_phys_vid_control_vblank_irq(phys_enc, false);
		dpu_encoder_helper_unregister_irq(phys_enc, INTR_IDX_UNDERRUN);
	}
}
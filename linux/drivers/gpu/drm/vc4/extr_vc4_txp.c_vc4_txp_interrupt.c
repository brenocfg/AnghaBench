#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* state; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct vc4_txp {TYPE_3__ connector; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TXP_DST_CTRL ; 
 int TXP_EI ; 
 int TXP_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXP_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_writeback_signal_completion (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_vc4_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_crtc_handle_vblank (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t vc4_txp_interrupt(int irq, void *data)
{
	struct vc4_txp *txp = data;

	TXP_WRITE(TXP_DST_CTRL, TXP_READ(TXP_DST_CTRL) & ~TXP_EI);
	vc4_crtc_handle_vblank(to_vc4_crtc(txp->connector.base.state->crtc));
	drm_writeback_signal_completion(&txp->connector, 0);

	return IRQ_HANDLED;
}
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
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {TYPE_1__* s_sendcontext; int /*<<< orphan*/  s_iowait; } ;
struct TYPE_2__ {int /*<<< orphan*/  waitlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_sc_wantpiobuf_intr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  iowait_pio_drain (int /*<<< orphan*/ *) ; 
 scalar_t__ iowait_pio_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qp_pio_drain(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;

	if (!priv->s_sendcontext)
		return;
	while (iowait_pio_pending(&priv->s_iowait)) {
		write_seqlock_irq(&priv->s_sendcontext->waitlock);
		hfi1_sc_wantpiobuf_intr(priv->s_sendcontext, 1);
		write_sequnlock_irq(&priv->s_sendcontext->waitlock);
		iowait_pio_drain(&priv->s_iowait);
		write_seqlock_irq(&priv->s_sendcontext->waitlock);
		hfi1_sc_wantpiobuf_intr(priv->s_sendcontext, 0);
		write_sequnlock_irq(&priv->s_sendcontext->waitlock);
	}
}
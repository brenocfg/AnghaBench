#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rvt_qp {struct qib_qp_priv* priv; } ;
struct qib_qp_priv {int /*<<< orphan*/  s_dma_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void qib_notify_qp_reset(struct rvt_qp *qp)
{
	struct qib_qp_priv *priv = qp->priv;

	atomic_set(&priv->s_dma_busy, 0);
}